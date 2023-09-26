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

// let testing = {}
// testing["Chicken"] = "Tasty"
// testing["bruh"] = 'bro'
// SetUrlValues(testing)

GetUrlValues();
// LogCurrentUrlValues();