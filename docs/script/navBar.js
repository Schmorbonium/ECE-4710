let SideBarLU = {}
let activeItem = null;
const urlActivePage = "ActivePage"

function newSidebarItem(Text, type, reference, pageKey) {
    let entry = {}
    entry.type = type;
    entry.item = document.createElement('li')
    const textArea = document.createElement('a')
    textArea.innerText = Text
    entry.item.appendChild(textArea)
    if(type == "markDown"){
        entry.ref = reference;
        entry.setActive = function (){
            setMD(`markdown/${entry.ref}`)
        }
        entry.item.addEventListener("click", function() {
            selectTab(pageKey)
        })
    }else if(type == "group"){
        submenu = document.createElement('ul')
        buildMenu(reference, submenu,(pageKey+"/"))
        entry.item = createCollapsibleDiv(entry.item,submenu)
        entry.setActive = function (){
        }
        // entry.setActive = function (){
        //     setMD(`markdown/${entry.file}`)
        // }

    }else{
        // entry.item.appendChild(textArea)
        entry.setActive = function (){
        }
        entry.item.addEventListener("click", function() {
            selectTab(pageKey)
        })
    }
    return entry
}

function selectTab(pageKey) {
    if (SideBarLU[pageKey] != null) {
        if(activeItem){
            activeItem.classList.remove("highlight")
        }
        SideBarLU[pageKey].item.classList.add("highlight")
        activeItem = SideBarLU[pageKey].item
        SideBarLU[pageKey].setActive()
        setUrlVar(urlActivePage,pageKey)
    }
}

function buildMenu(jsonData, parent,path=""){
    jsonData.forEach(element => {
        let entry = newSidebarItem(element.text, element.type, element.ref,(path+element.key),path)
        SideBarLU[(path+element.key)] = entry
        parent.appendChild(entry.item)
    });
}

async function buildSidebar() {
    const jsonFilePath = 'sideBar.json'
    const sideBar = document.getElementById('TheSideBar')
    try {
        var response = await fetch(jsonFilePath)
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        const json = await response.json();
        buildMenu(json, sideBar)
        // json.forEach(element => {
        //     let entry = newSidebarItem(element.text, element.type, element.ref,element.key)
        //     SideBarLU[element.key] = entry
        //     sideBar.appendChild(entry.item)
        // });
    } catch (error) {
        console.error("Error loading JSON:", error);
    }
    let StartingKey = Object.keys(SideBarLU)[0];
    if(getUrlVar(urlActivePage) != null){
        StartingKey = getUrlVar(urlActivePage)
    }
    selectTab(StartingKey)
}

async function setMD(markDownFile) {
    await setActiveMarkdown(markDownFile);
    await InsertPacketDocs();
}