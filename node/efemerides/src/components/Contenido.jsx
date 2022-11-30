import './Contenido.css'
import Formulario from './Formulario'

export default function Contenido(props) {

    function contenedor() {
        switch (props.estado) {
            case "sol":
                return <Formulario tipo={props.estado}/>
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
    return (
        <div className='contenido'>
            {contenedor()}
        </div>
    )


}