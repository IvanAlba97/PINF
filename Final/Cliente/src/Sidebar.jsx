import { useState } from 'react';
import './Sidebar.css';
import { Link } from 'react-router-dom';

export default function SideBar() {
  const tipos = [
    'Sol',
    'Luna',
    'Eclipses de Sol y Luna',
    'Ocultaciones',
    'Miscelanea',
  ];
  const [seleccion, setSeleccion] = useState(-1);

  function enlace(tipo) {
    if (tipo.replace(/\s+/g, '') == 'EclipsesdeSolyLuna') {
      return 'Eclipses';
    } else {
      return tipo.replace(/\s+/g, '');
    }
  }

  const listItems = tipos.map((tipo, key) => (
    <li>
      <Link
        to={enlace(tipo)}
        onClick={() => setSeleccion(key)}
        style={{ opacity: key == seleccion ? '1' : '0.5' }}
      >
        {tipo}
      </Link>
    </li>
  ));

  return (
    <div className='fondo'>
      <div>
        <h1>Efemérides</h1>
        <nav>
          <ul>{listItems}</ul>
        </nav>
      </div>
      <img src='/escudoArmada.webp' />
    </div>
  );
}
