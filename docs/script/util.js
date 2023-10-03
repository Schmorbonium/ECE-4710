// // let a = 'myName', b = 'Linuxhint';
// // let c = 'myTopic', d = 'JavaScript';
// // let myURL = new URL(window.location.href);
// // myURL.searchParams.set(a, b);
// // myURL.searchParams.set(c, d);
// // window.history.pushState({ path: myURL.href }, '');
// let para = location.search.substring(1).split("&");
// console.log('The passed value of through the value is : ', para)

let localUrlVars = {};
function GetUrlValues() {
    let Vars= location.search.substring(1);
    if(Vars.length <= 1){
        localUrlVars = {}
        return
    }
    let para = Vars.split("&");
    for (let index = 0; index < para.length; index++) {
        const element = para[index].split("=");
        // console.log(para)
        localUrlVars[element[0]] = element[1]
    }
}


function LogCurrentUrlValues(){
    string = 'Local Url Variables:\n'
    for(let x in localUrlVars){
        string +=`   ${x}=${localUrlVars[x]}\n`
    }
    console.log(string)
    console.log(localUrlVars)
    return string;
}

function GenerateUrlValues(vars){
    string = "?"
    for (let x in vars) {
        if(string != "?"){
            string+='&'
        }
        string+=`${x}=${vars[x]}`
      }
      return string;
}

function SetUrlValues(vars){
    let s = GenerateUrlValues(vars)
    window.history.replaceState(null,null,s)
}

function getUrlVar(variable){
    return localUrlVars[variable];
}

function setUrlVar(variable,value){
    localUrlVars[variable] = value
    SetUrlValues(localUrlVars)
}

const ExpandableHint = "[+]"
const CollapsibleHint = "[-]"
function createCollapsibleDiv(label, content) {
    const div = document.createElement('div')
    const textIndicator = document.createElement('span')
    textIndicator.textContent = ExpandableHint
    textIndicator.style = "padding:0px 10px 0px 0px"
    label.append(textIndicator)
    label.classList.add("collapsible")
    label.addEventListener('click', function () {
        if (content.style.display === 'block') {
            content.style.display = 'none';
            textIndicator.textContent = ExpandableHint
        } else {
            content.style.display = 'block';
            textIndicator.textContent = CollapsibleHint
        }
    })
    content.style.display = 'none'
    div.append(label, content)
    return div
}

// let testing = {}
// testing["Chicken"] = "Tasty"
// testing["bruh"] = 'bro'
// SetUrlValues(testing)

GetUrlValues();
// LogCurrentUrlValues();