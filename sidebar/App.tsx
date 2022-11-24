import { useState } from "react";
import "./App.css";

function App() {


  async function busqueda() {
    let res = await fetch("http://192.168.2.175/cgi-bin/enfecha.cgi");
    res = await res.json();

    return res;
  }

  const onClick = () => (busqueda().then((res) => console.log(res)))
  
  return (
    <div className="flex mt-20">
      <h1 className="mx-auto text-4xl text-titulo font-bold">Fenómenos de Sol para una fecha</h1>
      <button onClick={onClick}>hola</button>
    </div>
  );
}

export default App;
