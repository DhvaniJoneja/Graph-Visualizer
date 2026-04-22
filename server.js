process.on("uncaughtException", err => {
  console.error("UNCAUGHT ERROR:", err);
});

process.on("unhandledRejection", err => {
  console.error("UNHANDLED PROMISE:", err);
});

require("dotenv").config();
const API_KEY = process.env.GEMINI_API_KEY;
const express = require("express");
const { spawn } = require("child_process");
const path = require("path");
const cors = require("cors");
const fs = require("fs");
const multer = require("multer");

const app = express();

app.use(cors());
app.use(express.json());

app.use(express.static(path.join(__dirname, "public")));
app.get("/", (req, res) => {
  res.sendFile(path.join(__dirname, "public/index.html"));
});

app.post("/run", (req, res) => {
  console.log("REQ RECEIVED:", req.body);

  const { nodes, edges, algo, directed, weighted, source } = req.body;

  let input = "";

  let isDirected = directed ? 1 : 0;
  let isWeighted = weighted ? 1 : 0;

  input += `${nodes.length} ${edges.length} ${isDirected} ${isWeighted}\n`;

  edges.forEach(e => {
    if (isWeighted)
      input += `${e.from} ${e.to} ${e.weight || 1}\n`;
    else
      input += `${e.from} ${e.to}\n`;
  });

  input += `${algo} ${source}\n`;

  console.log("INPUT TO C++:\n" + input);

  const child = spawn("./backend/engine");

  let output = "";

  child.stdout.on("data", (data) => {
    output += data.toString();
  });

  child.stderr.on("data", (data) => {
    console.error("C++ ERROR:", data.toString());
  });

  child.on("close", () => {
    console.log("C++ OUTPUT:\n", output);
    res.send(output || "NO OUTPUT");
  });

  child.stdin.write(input);
  child.stdin.end();
});

const upload = multer({ dest: "uploads/" });

app.post("/upload", upload.single("file"), async (req, res) => {
  try {
    const code = fs.readFileSync(req.file.path, "utf-8");

    const llmOutput = await callLLM(code);
    console.log("LLM OUTPUT:\n", llmOutput);

    if (!llmOutput) {
      return res.json({ error: "LLM failed" });
    }

    const edges = [];
    let isDirected = false;
    let isWeighted = false;

    const lines = llmOutput.trim().split("\n");

    if (lines[0].startsWith("TYPE")) {
      const parts = lines[0].split(" ");
      isDirected = parts[1] === "directed";
      isWeighted = parts[2] === "weighted";
    }

    for (let i = 1; i < lines.length; i++) {
      const parts = lines[i].trim().split(/\s+/);

      if (parts.length === 3) {
        edges.push({
          from: Number(parts[0]),
          to: Number(parts[1]),
          weight: Number(parts[2])
        });
      }
      else if (parts.length === 2) {
        edges.push({
          from: Number(parts[0]),
          to: Number(parts[1]),
          weight: 1
        });
      }
    }

    res.json({ edges, isDirected, isWeighted });

  } catch (err) {
    console.error("UPLOAD ERROR:", err);
    res.json({ error: "Something went wrong" });
  }
});

async function callLLM(code) {
  try {
    const response = await fetch(
      `https://generativelanguage.googleapis.com/v1beta/models/gemini-3-flash-preview:generateContent?key=${API_KEY}`,
      {
        method: "POST",
        headers: {
          "Content-Type": "application/json"
        },
        body: JSON.stringify({
          contents: [
            {
              parts: [
                {
                  text: `Convert the given C++ graph code into a list of edges.

Also detect graph type.

OUTPUT FORMAT (STRICT):

First line:
TYPE <directed|undirected> <weighted|unweighted>

Then edges:
- Weighted → u v w
- Unweighted → u v

No explanation.

Example:
TYPE directed weighted
0 1 5
1 2 3

TYPE undirected unweighted
0 1
1 2

CODE:
${code}`
                }
              ]
            }
          ]
        })
      }
    );

    const data = await response.json();
    console.log("FULL GEMINI RESPONSE:", JSON.stringify(data, null, 2));

    return data.candidates?.[0]?.content?.parts?.[0]?.text || "";

  } catch (err) {
    console.error("LLM ERROR:", err);
    return "";
  }
}

app.listen(3001, () => {
  console.log("Server running at http://localhost:3001");
});