import { useEffect, useState } from 'react';
import './Sidebar.css';
import { Link } from 'react-router-dom';

export default function SideBar() {
  const [seleccion, setSeleccion] = useState(-1);
  const [desplegado, setDesplegado] = useState(false);
  const [windowHeight, windowWidth] = useWindowSize();

  const tipos = [
    'Sol',
    'Luna',
    'Eclipses de Sol y Luna',
    'Ocultaciones',
    'Miscelánea',
  ];

  function enlace(tipo) {
    if (tipo.replace(/\s+/g, '') == 'EclipsesdeSolyLuna') {
      return 'Eclipses';
    } else {
      const quitarAcentos = (str) =>
        str.normalize('NFD').replace(/[\u0300-\u036f]/g, '');
      return quitarAcentos(tipo.replace(/\s+/g, ''));
    }
  }

  const listItems = tipos.map((tipo, key) => (
    <div className='seleccion'>
      <div style={{ opacity: key == seleccion ? '1' : '0' }}></div>
      <li>
        <Link
          to={enlace(tipo)}
          onClick={() => setSeleccion(key)}
          style={{
            color: key == seleccion ? 'var(--primary-fg-color)' : '#c7c7c780',
          }}
        >
          {tipo}
        </Link>
      </li>
    </div>
  ));

  function Desplegable() {
    if (desplegado) {
      return (
        <nav className='menuDesplegable'>
          <ul>{listItems}</ul>
        </nav>
      );
    }
  }

  function IconoMenu() {
    if (!desplegado) {
      return <img src='/menu.svg' alt='' />;
    } else {
      return <img src='/close.svg' alt='' />;
    }
  }

  // REACCIÓN AL CAMBIO DE SECCIÓN
  useEffect(() => {
    switch (window.location.pathname) {
      case '/Sol':
        setSeleccion(0);
        break;
      case '/Luna':
        setSeleccion(1);
        break;
      case '/Eclipses':
        setSeleccion(2);
        break;
      case '/Ocultaciones':
        setSeleccion(3);
        break;
      case '/Miscelanea':
        setSeleccion(4);
        break;
      default:
        break;
    }
    setDesplegado(false);
    window.scrollTo({ top: 0, behavior: 'smooth' });
  }, [seleccion]);

  // RENDERIZADO
  if (windowWidth > 1280) {
    return (
      <div className='fondo'>
        <div className='textoSidebar'>
          <h1>Efemérides</h1>
          <nav>
            <ul>{listItems}</ul>
          </nav>
        </div>
        <img src='/escudoArmada.webp' />
      </div>
    );
  } else {
    return (
      <div className='desplegable'>
        <header>
          <img className='logo' src='/escudoArmada.webp' />
          <h1>Efemérides</h1>
          <button
            onClick={() => {
              setDesplegado(!desplegado);
            }}
          >
            <IconoMenu />
          </button>
        </header>
        <Desplegable />
      </div>
    );
  }
}

// CONTROLA EL TAMAÑO DE LA VENTANA DEL NAVEGADOR
// DEVUELVE UNA LISTA CON LA ALTURA Y LA ANCHURA AL CAMBIAR EL TAMAÑO DE LA VENTANA
function useWindowSize() {
  const [size, setSize] = useState([window.innerHeight, window.innerWidth]);
  useEffect(() => {
    const handleResize = () => {
      setSize([window.innerHeight, window.innerWidth]);
    };
    window.addEventListener('resize', handleResize);
    return () => {
      window.removeEventListener('resize', handleResize);
    };
  }, []);
  return size;
}
