import { useEffect, useState } from "react"
import './Sidebar.css'
import { Link } from "react-router-dom"

export default function SideBar() {
    const [seleccion, setSeleccion] = useState(-1)
    const tipos = [
        "Sol",
        "Luna",
        "Eclipses de Sol y Luna",
        "Ocultaciones",
        "Miscelánea"
    ]

    useEffect(() => {
        switch (window.location.pathname) {
            case "/Sol":
                setSeleccion(0)
                break
            case "/Luna":
                setSeleccion(1)
                break
            case "/Eclipses":
                setSeleccion(2)
                break
            case "/Ocultaciones":
                setSeleccion(3)
                break
            case "/Miscelánea":
                setSeleccion(4)
                break
            default:
                break
        }
    })

    function enlace(tipo) {
        if (tipo.replace(/\s+/g, '') == "EclipsesdeSolyLuna") {
            return "Eclipses"
        }
        else {
            return tipo.replace(/\s+/g, '')
        }
    }

    const listItems = tipos.map((tipo, key) => (
        <li>
            <Link to={enlace(tipo)} onClick={() => setSeleccion(key)} style={{ opacity: key == seleccion ? '1' : '0.5' }}>{tipo}</Link>
        </li>
    ))

    return (
        <div className="fondo">
            <div>

                <h1>Efemérides</h1>
                <nav><ul>{listItems}</ul></nav>
            </div>
            <img src="/escudoArmada.webp" />
        </div>
    )
}