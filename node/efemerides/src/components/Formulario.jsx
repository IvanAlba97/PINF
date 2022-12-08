import { useState } from 'react'
import './Formulario.css'

export default function Formulario(props) {

    const [datos, setDatos] = useState(
        {
            latitud: 0,
            longitud: 0,
            gradosLat: 0,
            minutosLat: 0,
            gradosLong: 0, 
            minutosLong: 0,
            fecha: null,
            hora: 0,
            norteSur: null, // 0 Norte, 1 Sur
            esteOeste: null, //0 Este, 1 Oeste
            
        }
    )

    const actualizarLatitud = (estado) => { setDatos({...datos, latitud: estado}) }
    const actualizarLongitud = (estado) => { setDatos({...datos, longitud: estado}) }
    const actualizarGradosLat = (estado) => { setDatos({...datos, gradosLat: estado}) }
    const actualizarMinutosLat = (estado) => { setDatos({...datos, minutos: estado}) }
    const actualizarGradosLong = (estado) => { setDatos({...datos, gradosLong: estado}) }
    const actualizarMinutosLong = (estado) => { setDatos({...datos, minutosLong: estado}) }
    const actualizarFecha = (estado) => { setDatos({...datos, fecha:estado}) }
    const actualizarHora = (estado) => { setDatos({...datos, hora: estado}) }
    const actualizarNorteSur = (estado) => { setDatos({...datos, norteSur: estado}) }
    const actualizarEsteOeste = (estado) => { setDatos({...datos, esteOeste: estado}) }

    return (
        <div className="formulario">
            <h1 className='titulo'>Fenómenos de Sol para una fecha</h1>
            <form>
                <div className='apartado'>
                    <h2 className='posicion'>Posición</h2>
                    <div className='elementos'>
                        <InputNumber label="Latitud" value={datos.latitud} onChange={actualizarLatitud} />
                        <InputNumber label="Grados" value={datos.gradosLat} onChange={actualizarGradosLat} />
                        <InputNumber label="Minutos" value={datos.minutosLat} onChange={actualizarMinutosLat} />
                        <div>
                            <label className='inputLabel'>Orientación</label>
                            <div className='radioGroup'>
                                <Radio valor="Norte" name="Nortesur" />
                                <Radio valor="Sur" name="Nortesur" />
                            </div>
                        </div>
                    </div>
                    <div className="elementos">
                        <InputNumber label="Longitud" value={datos.longitud} onChange={actualizarLongitud} />
                        <InputNumber label="Grados" value={datos.gradosLong} onChange={actualizarGradosLong} />
                        <InputNumber label="Minutos" value={datos.longitud} onChange={actualizarMinutosLong} />
                        <div>
                            <label className='inputLabel'>Orientación</label>
                            <div className='radioGroup'>
                                <Radio valor="Este" name="EsteOeste" />
                                <Radio valor="Oeste" name="EsteOeste" />
                            </div>
                        </div>

                    </div>
                    <div className='apartado'>
                        <h2 className='posicion'>Fecha y Hora</h2>
                        <DatePicker />
                    </div>
                </div>
            </form>
        </div>
    )
}
function InputNumber({ label, value, onChange }) {
    const [valor, setValor] = useState('')
    const handleChange = (event) => {
        if (!isNaN(event.target.value) && event.target.value !== '') {
            setValor(event.target.value)
            onChange(parseInt(event.target.value))
        }
        else if (event.target.value === '') {
            setValor('')
            onChange(0)
        }
    }

    return (
        <div>
            <label className='inputLabel'>{label}</label>
            <input type="number" className='input' value={valor} min="0" placeholder="0" onChange={handleChange}></input>
        </div>
    )
}

function InputHoraUTC({ label }) {
    <div>
        <label className='inputLabel'>{label}</label>
        <input className='input' type="number" min="-11" max="12"></input>
    </div>
}

function DatePicker({ label }) {
    return (<div>
        <label className='inputLabel'>{label}</label>
        <input type="date" ></input>
    </div>)
}
function Radio({ name, valor }) {
    return (
        <div className='radioContainer'>
            <input type="radio" name={name} value={valor} />
            <label htmlFor={name}>{valor}</label>
        </div>
    )
}