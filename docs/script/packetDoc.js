const packetClass = "PacketDoc"
var collapsibleCount = 0

function createPacketTableHeader(name, width) {
    const tableHeader = document.createElement('thead')

    const labelRow = document.createElement('tr')
    tableHeader.appendChild(labelRow)
    const labelCol = document.createElement('th')
    labelRow.appendChild(labelCol)
    labelCol.innerText = name
    labelCol.colSpan = width

    const bitRow = document.createElement('tr')
    for (let i = 0; i < width; i++) {
        const bit = document.createElement('th')
        bit.classList.add('bitBox')
        bit.innerText = width - 1 - i
        bitRow.appendChild(bit)
    }
    tableHeader.appendChild(bitRow)

    return tableHeader
}

function createPacketTableBody(jsonData, width) {
    const body = document.createElement('tbody')
    var curRow = document.createElement('tr')
    body.appendChild(curRow)
    var cnt = 0
    if (!jsonData["fields"]) {
        return body
    }

    jsonData["fields"].forEach(element => {
        if (cnt == width) {
            cnt = 0
            curRow = document.createElement('tr')
            body.appendChild(curRow)
        }
        if (cnt + element.bits <= width) {
            cnt += element.bits
            const cell = document.createElement('td')
            cell.colSpan = element.bits
            cell.innerText = element.name
            curRow.appendChild(cell)
        }
    });
    return body
}

function generateTable(jsonData) {
    const table = document.createElement('table')
    table.appendChild(
        createPacketTableHeader(jsonData.name, jsonData.wordSize))
    table.appendChild(
        createPacketTableBody(jsonData, jsonData.wordSize))
    return table
}

function generatePktEnumTable(options) {
    const table = document.createElement('table')
    {
        const tHead = document.createElement('thead')
        table.appendChild(tHead)
        const r = tHead.insertRow()
        r.insertCell().innerText = "Value"
        r.insertCell().innerText = "Packet"
    }
    {
        const tbody = document.createElement('tbody')
        table.appendChild(tbody)
        options.forEach(option => {
            const r = tbody.insertRow()
            r.insertCell().innerText = option.value
            const linkedPacket = document.createElement('a')
            linkedPacket.href = `#${option.ResultingPacketType}`
            linkedPacket.innerText = option.ResultingPacketType
            r.insertCell().appendChild(linkedPacket) 
        });
    }
    return table
}

function generateEnumTable(options) {
    const table = document.createElement('table')
    {
        const tHead = document.createElement('thead')
        table.appendChild(tHead)
        const r = tHead.insertRow()
        r.insertCell().innerText = "Value"
        r.insertCell().innerText = "Description"
    }
    {
        const tbody = document.createElement('tbody')
        table.appendChild(tbody)
        options.forEach(option => {
            const r = tbody.insertRow()
            r.insertCell().innerText = option.value
            r.insertCell().innerText = option.result
        });
    }
    return table
}

function subFieldDes(jsonData) {
    div = document.createElement('div')
    if(!jsonData.fields){
        return div
    }
    jsonData.fields.forEach(element => {
        div.appendChild(getFieldDes(element))
    });
    return div
}


function subfieldLayout(jsonData) {
    const table = document.createElement('table')

    const tableHeader = createPacketTableHeader(jsonData.name, jsonData.bits)
    table.appendChild(tableHeader)

    const tableBody = createPacketTableBody(jsonData, jsonData.bits)
    table.appendChild(tableBody)

    return table
}

function subFieldsDoc(jsonData) {
    const div = document.createElement('div')
    div.appendChild(
        subfieldLayout(jsonData)
    )
    div.appendChild(
        subFieldDes(jsonData)
    )
    return div
}

function getFieldDes(jsonData) {
    var div = document.createElement('div')
    div.classList.add('nested')
    
    if(jsonData.fieldType == "unused"){
        return div
    }
    const header = document.createElement('h3')
    div.appendChild(header)
    header.innerText = jsonData.name
    
    const content = document.createElement('div')
    div.appendChild(content)
    content.classList.add('nested')
    
    if (jsonData.def) {
        const definition = document.createElement('p')
        definition.innerText = jsonData.def
        content.appendChild(definition)
    }

    if (jsonData.fieldType == 'enum') {
        content.appendChild(generateEnumTable(jsonData.options))
    }

    if (jsonData.fieldType == 'pktEnum') {
        content.appendChild(generatePktEnumTable(jsonData.options))
    }

    if (jsonData.fieldType == "SuperField") {
        content.appendChild(subFieldsDoc(jsonData))
    }
    div = createCollapsibleDiv(header, content)
    return div
}


function generateDescriptions(jsonData) {
    const des = document.createElement('div')
    jsonData["fields"].forEach(element => {
        des.appendChild(getFieldDes(element))
    });
    return des
}

function createCollapsibleDiv(label, content) {
    const div = document.createElement('div')
    label.classList.add("collapsible")
    label.addEventListener('click', function () {
        if (content.style.display === 'block') {
            content.style.display = 'none';
        } else {
            content.style.display = 'block';
        }
    })
    content.style.display = 'none'
    div.append(label, content)
    return div
}

async function InsertPacketDoc(packDoc) {
    var jsonFilePath = `packetDefs/${packDoc.id}.json`
    try {
        var response = await fetch(jsonFilePath)
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        const AllJson = await response.json();
        const t = document.createElement('div')
        var subPacket = packDoc.dataset.sub_pkt
        // console.log(subPacket)
        if(!subPacket){
            subPacket = "header"
        }
        // console.log(AllJson)
        // console.log(AllJson[subPacket])
        const json = AllJson[subPacket]
        const label = document.createElement('h2')
        label.innerText = json.name

        const Docs = document.createElement('div')
        Docs.classList.add("content", "nested")
        Docs.style.display = 'none';
        const packetTable =
            Docs.appendChild(generateTable(json))
        Docs.appendChild(generateDescriptions(json))
        const CPD = createCollapsibleDiv(label, Docs)
        packDoc.appendChild(CPD)

    } catch (error) {
        console.error("Error loading JSON:", error);
    }
}

async function InsertPacketDocs() {
    var packetDocs = document.getElementsByClassName(packetClass);
    for (var i = 0; i < packetDocs.length; i++) {
        var packetDoc = packetDocs[i];
        // console.log(packetDoc)
        await InsertPacketDoc(packetDoc)
    }
}

