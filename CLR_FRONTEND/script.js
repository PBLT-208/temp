function generateTables() {
  const grammar = document.getElementById("grammarInput").value;
  if (!grammar.trim()) {
    alert("Please enter a grammar.");
    return;
  }

  // Placeholder: Replace this with actual CLR(1) parser logic
  document.getElementById("firstFollowSets").innerText = "FIRST and FOLLOW sets computed here...";
  document.getElementById("itemSets").innerText = "Canonical LR(1) Items listed here...";
  document.getElementById("parsingTable").innerText = "ACTION and GOTO tables generated here...";
}

function parseString() {
  const inputStr = document.getElementById("inputString").value;
  if (!inputStr.trim()) {
    alert("Please enter an input string.");
    return;
  }

  // Placeholder: Replace this with actual parsing logic
  document.getElementById("parsingProcess").innerText = "Parsing steps shown here...";
  document.getElementById("result").innerText = "✅ String is syntactically correct.";
}
