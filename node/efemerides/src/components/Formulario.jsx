import { useState } from 'react'
import './Formulario.css'

export default function Formulario(props) {
    let [latitud, setLatitud] = useState(0)
    let [grados, setGrados] = useState(0)
    let [minutos, setMinutos] = useState(0)
    let [fecha, setFecha] = useState(null)
    let [hora, setHora] = useState(0)

    const actualizarLatitud = (estado) => { setLatitud(estado) }
    const actualizarGrados = (estado) => { setGrados(estado) }
    const actualizarMinutos = (estado) => { setMinutos(estado) }
    const actualizarFecha = (estado) => { setFecha(estado) }
    const actualizarHora = (estado) => { setHora(estado) }

    return (
        <div className="formulario">
            <h1 className='titulo'>Fenómenos de Sol para una fecha</h1>
            <form>
                <div className='apartado'>
                    <h2 className='posicion'>Posición</h2>
                    <div className='elementos'>
                        <InputNumber label="Latitud" value={latitud} onChange={actualizarLatitud} />
                        <InputNumber label="Grados" value={grados} onChange={actualizarGrados} />
                        <InputNumber label="Minutos" value={minutos} onChange={actualizarMinutos} />
                        <div>
                            <label className='inputLabel'>Orientación</label>
                            <div className='radioGroup'>
                                <Radio valor="Norte" name="Nortesur" />
                                <Radio valor="Sur" name="Nortesur" />
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
    const [valor,setValor] = useState('')
    const handleChange = (event) => {
        if (!isNaN(event.target.value) && event.target.value !== '') {
            setValor(event.target.value)
            onChange(parseInt(event.target.value))
        }
        else if(event.target.value === '' )
        {
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