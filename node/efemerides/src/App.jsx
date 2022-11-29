import './App.css'
import Sidebar from "./Sidebar"
import { Routes, Route } from "react-router-dom"
import Contenido from "./Contenido"

function App() {
  return (
    <>
      <div className='container'>
        <Sidebar />
        <Routes>
          <Route path="/" element={<Contenido estado={"nada"}></Contenido>}/>
          <Route path="/Sol" element={<Contenido estado={"sol"}></Contenido>}/>
          <Route path="/Luna" element={<Contenido estado={"luna"}></Contenido>}/>
          <Route path="/Eclipses" element={<Contenido estado={"eclipses"}></Contenido>}/>
          <Route path="/Ocultaciones" element={<Contenido estado={"ocultaciones"}></Contenido>}/>
          <Route path="/Miscelánea" element={<Contenido estado={"miscelanea"}></Contenido>}/>
        </Routes>
      </div>
    </>
  )
}

export default App
