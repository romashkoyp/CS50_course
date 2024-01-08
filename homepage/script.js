// Show hidden content
function toggleContent() {
    var hiddenContent = document.getElementById("hidden-content");
    if (hiddenContent.style.display === "none") {
        hiddenContent.style.display = "block"; // Show the content
    } else {
        hiddenContent.style.display = "none"; // Hide the content
    }
}