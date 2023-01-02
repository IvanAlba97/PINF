import './App.css';
import Sidebar from './components/Sidebar';
import { Routes, Route } from 'react-router-dom';
import Contenido from './components/Contenido';

function App() {
  return (
    <>
      <div className='container'>
        <Sidebar />
        <Routes>
          <Route path='/' element={<Contenido estado={'nada'}></Contenido>} />
          <Route path='/sol' element={<Contenido estado={'sol'}></Contenido>} />
          <Route
            path='/luna'
            element={<Contenido estado={'luna'}></Contenido>}
          />
        </Routes>
      </div>
    </>
  );
}

export default App;
