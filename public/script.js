// Graph init
let nodes = new vis.DataSet();
let edges = new vis.DataSet();

let network;

window.onload = function () {
  network = new vis.Network(
    document.getElementById("graph"),
    { nodes, edges },
    {}
  );
};

function addEdgesBulk() {
  let input = document.getElementById("edgesInput").value.trim();
  let lines = input.split("\n");

  let isDirected = document.getElementById("directed").checked;
  let isWeighted = document.getElementById("weighted").checked;

  lines.forEach(line => {
    let parts = line.trim().split(/\s+/);
    if (parts.length < 2) return;

    let u = parseInt(parts[0]);
    let v = parseInt(parts[1]);
    let w = parts[2] ? parseInt(parts[2]) : 1;
    if (!nodes.get(u)) nodes.add({ id: u, label: "Node " + u });
    if (!nodes.get(v)) nodes.add({ id: v, label: "Node " + v });

    let edge = {
      id: u + "-" + v + "-" + Date.now() + Math.random(),
      from: u,
      to: v
    };

    if (isDirected) edge.arrows = "to";
    if (isWeighted) {
      edge.label = String(w);
      edge.weight = w;
    }

    edges.add(edge);
  });

}

function clearGraph() {
  nodes.clear();
  edges.clear();
  document.getElementById("edgesInput").value = "";
}


function animateSteps(data) {
  let steps = data.trim().split(/\r?\n/);

  steps.forEach((step, i) => {
    setTimeout(() => {
      let parts = step.trim().split(" ");

      if (parts[0] === "VISIT") {
        let node = parseInt(parts[1]);

        nodes.update({
          id: node,
          color: {
            background: "#d65eeb",
            border: "#ecf0f4"
          },
          font: {
            color: "#ffffff"
          }
        });
      }

      else if (parts[0] === "EDGE") {
        let u = parseInt(parts[1]);
        let v = parseInt(parts[2]);

        edges.get().forEach(e => {
          if ((e.from == u && e.to == v) || (e.from == v && e.to == u)) {
            edges.update({
              id: e.id,
              color: { color: "#df9aec" }
            });
          }
        });
      }
      else if (parts[0] === "DIST") {
        let node = parseInt(parts[1]);
        let value = parts[2];

        nodes.update({
          id: node,
          label: `Node ${node}\n(${value})`
        });
      }
      else if (parts[0] === "RESULT_NODE") {
        let node = parseInt(parts[1]);

        nodes.update({
          id: node,
          color: {
            background: "#22c55e"
          },
          font: {
            color: "#000"
          }
        });
      }

      else if (parts[0] === "RESULT_EDGE") {
        let u = parseInt(parts[1]);
        let v = parseInt(parts[2]);

        edges.get().forEach(e => {
          if ((e.from == u && e.to == v) || (e.from == v && e.to == u)) {
            edges.update({
              id: e.id,
              color: { color: "#22c55e" }
            });
          }
        });
      }

    }, i * 500);
  });
}


async function runAlgo() {
  let nodeList = nodes.get();
  let edgeList = edges.get();
  let algo = document.getElementById("algo").value;

  let source = parseInt(document.getElementById("source").value);
  if (isNaN(source)) source = 0;

  let res = await fetch("http://localhost:3001/run", {
    method: "POST",
    headers: {
      "Content-Type": "application/json"
    },
    body: JSON.stringify({
      nodes: nodeList,
      edges: edgeList,
      algo: algo,
      directed: document.getElementById("directed").checked,
      weighted: document.getElementById("weighted").checked,
      source: source
    })
  });

  let data = await res.text();
  document.getElementById("output").innerText = data;

  nodes.get().forEach(n => nodes.update({ id: n.id, color: null }));
  edges.get().forEach(e => edges.update({ id: e.id, color: null }));

  animateSteps(data);
}

document.getElementById("fileInput").addEventListener("change", function () {
  const file = this.files[0];
  document.getElementById("fileName").innerText =
    file ? file.name : "No file chosen";
});


async function uploadFile() {
  const fileInput = document.getElementById("fileInput");
  const file = fileInput.files[0];

  if (!file) {
    alert("Please choose a .cpp file first");
    return;
  }

  const formData = new FormData();
  formData.append("file", file);

  try {
    const res = await fetch("http://localhost:3001/upload", {
      method: "POST",
      body: formData
    });

    const data = await res.json();

    console.log("Backend response:", data);

    if (data.edges) {
      loadFromLLM(data);
    }

  } catch (err) {
    console.error("Upload failed:", err);
    alert("Error uploading file");
  }
}


function loadFromLLM(data) {
  nodes.clear();
  edges.clear();

  document.getElementById("directed").checked = data.isDirected;
  document.getElementById("weighted").checked = data.isWeighted;

  data.edges.forEach(e => {
    if (!nodes.get(e.from)) nodes.add({ id: e.from, label: "Node " + e.from });
    if (!nodes.get(e.to)) nodes.add({ id: e.to, label: "Node " + e.to });

    let edge = {
      id: e.from + "-" + e.to + "-" + Math.random(),
      from: e.from,
      to: e.to
    };

    if (data.isDirected) edge.arrows = "to";

    if (data.isWeighted) {
      edge.label = String(e.weight);
      edge.weight = e.weight;
    }

    edges.add(edge);
  });

  network.fit();
}


function loadGraph(edgeList) {
  nodes.clear();
  edges.clear();

  edgeList.forEach(([u, v, w]) => {

    if (!nodes.get(u)) nodes.add({ id: u, label: "Node " + u });
    if (!nodes.get(v)) nodes.add({ id: v, label: "Node " + v });

    let edge = {
      id: u + "-" + v + "-" + Math.random(),
      from: u,
      to: v
    };

    if (document.getElementById("directed").checked) {
      edge.arrows = "to";
    }

    if (document.getElementById("weighted").checked) {
      edge.label = String(w);
      edge.weight = w;
    }

    edges.add(edge);
  });

  network.fit();
}