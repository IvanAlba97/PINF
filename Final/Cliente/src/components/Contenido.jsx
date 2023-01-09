import './Contenido.css';
import Formulario from './Formulario';

export default function Contenido(props) {
  function contenedor() {
    switch (props.estado) {
      case 'sol':
        return <Formulario tipo={props.estado} nombre='sol' />;
      case 'luna':
        return <Formulario tipo={props.estado} nombre='luna' />;
      default:
        return (
          <div className='default'>
            <h1>Selecciona la opción deseada</h1>
          </div>
        );
    }
  }

  return (
    <div className='contenido'>
      {contenedor()}
      <img src='observatorio.webp' alt='observatorio' />
    </div>
  );
}
