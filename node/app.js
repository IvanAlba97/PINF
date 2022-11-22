async function f(){
    const response = await fetch("http://192.168.253.175/cgi-bin/enfecha.cgi");
    console.log(await response.text());
}

f().catch((text) => console.log("Error"));
