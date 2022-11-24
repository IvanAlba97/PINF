import { useState } from "react";
import './Sidebar.css'

export default function SideBar() {
    const tipos = [
        "Sol",
        "Luna",
        "Eclipses de Sol y Luna",
        "Ocultaciones",
        "Miscelanea",
    ];
    const [seleccion, setSeleccion] = useState(-1);

    const listItems = tipos.map((tipo, key) => (
            <button onClick={() => setSeleccion(key)} style={{opacity: key == seleccion ? '1' : '0.5'}}>
                {tipo}
            </button>
    ));

    return (
        <div className="fondo">
            <div>
                <h1>Efemérides</h1>
                <div>{listItems}</div>
            </div>
            <img src="/escudoArmada.webp"/>
        </div>
    );
}