import './Contenido.css'
import Formulario from './Formulario'

export default function Contenido(props) {

    function contenedor() {
        switch (props.estado) {
            case "sol":
                return <Formulario tipo={props.estado} nombre='Sol' />
            case "luna":
                return <Formulario tipo={props.estado} nombre='Luna' />
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
    return (
        <div className='contenido'>
            {contenedor()}
            <img src="observatorio.webp" alt="observatorio" />
        </div>
    )


}