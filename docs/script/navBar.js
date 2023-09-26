let SideBarLU = {}
let activeItem = null;
const urlActivePage = "ActivePage"

function newSidebarItem(Text, type, file, pageKey) {
    let entry = {}
    entry.type = type;
    entry.file = file;
    entry.item = document.createElement('li')
    entry.item.addEventListener("click", function() {
        selectTab(pageKey)
    })
    const textArea = document.createElement('a')
    entry.item.appendChild(textArea)
    textArea.innerText = Text
    if(type == "markDown"){
        entry.setActive = function (){
            setMD(`markdown/${entry.file}`)
        }
    }else{
        entry.setActive = function (){
        }
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

async function buildSidebar() {
    const jsonFilePath = 'sideBar.json'
    const sideBar = document.getElementById('TheSideBar')
    try {
        var response = await fetch(jsonFilePath)
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        const json = await response.json();
        json.forEach(element => {
            let entry = newSidebarItem(element.text, element.type, element.ref,element.key)
            SideBarLU[element.key] = entry
            sideBar.appendChild(entry.item)
        });
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