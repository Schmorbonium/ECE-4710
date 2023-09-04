
showdown.setOption('tasklists', 'true');
showdown.setOption('simplifiedAutoLink', 'true');
showdown.setOption('ghMentions', 'true');
showdown.setOption('simpleLineBreaks', 'true');
showdown.setOption('tables', 'true');

async function setActiveMarkdown(markdownFilePath) {
    await fetch(markdownFilePath)
        .then(response => response.text())
        .then(async markdownText => {
            var markdownConverter = new showdown.Converter();
            var htmlContent = markdownConverter.makeHtml(markdownText);
    
            var markdownContainer = document.getElementById("markdownContent");
            markdownContainer.innerHTML = htmlContent;
        })
        .catch(error => {
            console.error("Error loading Markdown:", error);
        });
}