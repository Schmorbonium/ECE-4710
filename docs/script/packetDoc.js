const packetClass = "PacketDoc"
var collapsibleCount = 0

function generateTable(jsonData) {
    var tableHTML = `<table><thead><tr><th colspan=${jsonData.wordSize}>${jsonData.name}</th></tr>`;

    tableHTML += "<tr>"
    for (let i = 0; i < jsonData.wordSize; i++) {
        tableHTML += `<th>${jsonData.wordSize - 1 - i}</th>`
    }
    tableHTML += "</tr></thead><tbody><tr>"

    var cnt = 0
    jsonData["fields"].forEach(element => {
        if (cnt == jsonData.wordSize) {
            cnt = 0
            tableHTML += "</tr><tr>"
        }
        if (cnt + element.bits <= jsonData.wordSize) {
            cnt += element.bits
            tableHTML += `<td colspan=${element.bits}>${element.name}</td>`;
            if (cnt == jsonData.wordSize) {
            }
        }
    });
    tableHTML += "</tr></tbody></table>";
    return tableHTML
}

function generateOptionsTable(options){
    var table = "<table><thead><tr><th>Value</th><th>Description</th></tr></thead>"
    options.forEach(option => {
        table+=`<tr><td>${option.value}</td><td>${option.result}</td></tr>`
    });
    table += "</table>"
    return table
}

function subFieldDes(jsonData){
    des = ""
    jsonData.subFields.forEach(element => {
        des += getFieldDes(element)
    });
    return des
}

function Buildtable(Title,colCnt,){

}

function subfieldLayout(jsonData){

    return ""
}

function subFieldsDoc(jsonData){
    // console.log(`${subfieldLayout(jsonData)}${subFieldDes(jsonData)}`)
    return `${subfieldLayout(jsonData)}${subFieldDes(jsonData)}`
}

function getFieldDes(jsonData){
    var des = ""
    if(jsonData.def){
        des += `<h3>${jsonData.name}</h3>`
        des += `<p class="nested">${jsonData.def}</p>`
        if(jsonData.options){
            des += generateOptionsTable(jsonData.options)
        }
        if(jsonData.fieldType == "SuperField"){
            des += subFieldsDoc(jsonData)
        }
    }
    return `<div class="nested">${des}</div>`
}


function generateDescriptions(jsonData){
    var des = "<div>"
    jsonData["fields"].forEach(element => {
        des += getFieldDes(element)
    });
    des += "</div>"
    return des
}

function createCollapsibleDiv(label,content) {
    const div = document.createElement('div')
    label.classList.add("collapsible")
    label.addEventListener('click', function() {
        if (content.style.display === 'block') {
            content.style.display = 'none';
        } else {
            content.style.display = 'block';
        }
    })
    div.append(label,content)
    return div
}

async function InsertPacketDoc(packDoc) {
    var jsonFilePath = `packetDefs/${packDoc.id}.json`
    try {
        var response = await fetch(jsonFilePath)
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        const json = await response.json();

        const label = document.createElement('h2')
        label.innerText = json.name

        const Docs = document.createElement('div')
        Docs.classList.add("content","nested")
        Docs.style.display = 'none';
        Docs.innerHTML = `${generateTable(json)}${generateDescriptions(json)}`
        const CPD =  createCollapsibleDiv(label,Docs)
        packDoc.appendChild(CPD)
        // var packDoc = document.getElementById(packDoc.id);
        // const contentId = `collapsible-${packDoc.id}`
        // var html = 
        // `<h2 class="collapsible" data-target=${contentId}>${json.name}</h2>
        // <div id="${contentId}" class="content nested"  style="display: none;">
        //     ${generateTable(json)}
        //     ${generateDescriptions(json)}
        // </div>`
        // packDoc.innerHTML = html;
    } catch(error) {
        console.error("Error loading JSON:", error);        
    }
}

async function InsertPacketDocs() {
    var packetDocs = document.getElementsByClassName(packetClass);
    for (var i = 0; i < packetDocs.length; i++) {
        var packetDoc = packetDocs[i];
        await InsertPacketDoc(packetDoc)
    }
}