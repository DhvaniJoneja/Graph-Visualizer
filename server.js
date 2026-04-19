const express = require("express");
const { spawn } = require("child_process");
const path = require("path");
const cors = require("cors");

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

app.listen(3000, () => {
  console.log("🔥 Server running at http://localhost:3000");
});