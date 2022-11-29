// import './Contenido.css'

export default function Contenido(props) {
    switch (props.estado) {
        case "sol":
            return <p>Estás en sol</p>
        case "luna":
            return <p>Estás en luna</p>
        case "eclipses":
            return <p>Estás en eclipses</p>
        case "ocultaciones":
            return <p>Estás en ocultaciones</p>
        case "miscelanea":
            return <p>Estás en miscelanea</p>
        default:
            return <p>Selecciona</p>
    }
}