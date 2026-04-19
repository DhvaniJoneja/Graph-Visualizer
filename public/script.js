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

    // Add nodes safely
    if (!nodes.get(u)) nodes.add({ id: u, label: "Node " + u });
    if (!nodes.get(v)) nodes.add({ id: v, label: "Node " + v });

    let edge = {
      id: u + "-" + v + "-" + Date.now() + Math.random(),
      from: u,
      to: v
    };

    if (isDirected) edge.arrows = "to";

    // Weighted
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

  let res = await fetch("/run", {
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

  // reset graph
  nodes.get().forEach(n => nodes.update({ id: n.id, color: null }));
  edges.get().forEach(e => edges.update({ id: e.id, color: null }));

  animateSteps(data);
}