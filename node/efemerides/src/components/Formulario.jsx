import { useState } from 'react'
import './Formulario.css'

export default function Formulario({ nombre, enlace }) {
    const [datos, setDatos] = useState(
        {
            gradosLat: 0,
            minutosLat: 0,
            segundosLat: 0,
            segundosLong: 0,
            gradosLong: 0,
            minutosLong: 0,
            fecha: '',
            hora: 0,
            norteSur: undefined, // 0 Norte, 1 Sur
            esteOeste: undefined, //0 Este, 1 Oeste

        }
    )

    const actualizarGradosLat = (estado) => { setDatos({ ...datos, gradosLat: estado }) }
    const actualizarMinutosLat = (estado) => { setDatos({ ...datos, minutos: estado }) }
    const actualizarSegundosLat = (estado) => { setDatos({ ...datos, segundosLat: estado }) }
    const actualizarGradosLong = (estado) => { setDatos({ ...datos, gradosLong: estado }) }
    const actualizarMinutosLong = (estado) => { setDatos({ ...datos, minutosLong: estado }) }
    const actualaizarSegundosLong = (estado) => { setDatos({ ...datos, segundosLong: estado }) }
    const actualizarFecha = (estado) => { setDatos({ ...datos, fecha: estado }) }
    const actualizarHora = (estado) => { setDatos({ ...datos, hora: estado }) }
    const actualizarNorteSur = (estado) => { setDatos({ ...datos, norteSur: estado }) }
    const actualizarEsteOeste = (estado) => { setDatos({ ...datos, esteOeste: estado }) }

    return (
        <>
            <h1 className='titulo'>Fenómenos de {nombre} para una fecha</h1>
            <form className='formulario'>
                <div>
                    <h2 className='apartado'>Posición</h2>
                    <h4 className='subapartado'>Latitud</h4>
                    <div className='linea'>
                        <InputNumber label="Grados" value={datos.gradosLat} onChange={actualizarGradosLat} />
                        <InputNumber label="Minutos" value={datos.minutosLat} onChange={actualizarMinutosLat} />
                        <InputNumber label="Segundos" value={datos.segundosLat} onChange={actualizarSegundosLat} />
                        <div>
                            <label className='inputLabel'>Orientación</label>
                            <div className='radioContainer'>
                                <Radio valor="N" name="NorteSur" etiqueta='Norte' onSelect={actualizarNorteSur} />
                                <Radio valor="S" name="NorteSur" etiqueta='Sur' onSelect={actualizarNorteSur} />
                            </div>
                        </div>
                    </div>

                    <h4 className='subapartado'>Longitud</h4>
                    <div className="linea">
                        <InputNumber label="Grados" value={datos.gradosLong} onChange={actualizarGradosLong} />
                        <InputNumber label="Minutos" value={datos.longitud} onChange={actualizarMinutosLong} />
                        <InputNumber label="Segundos" value={datos.segundosLong} onChange={actualaizarSegundosLong} />
                        <div>
                            <label className='inputLabel'>Orientación</label>
                            <div className='radioContainer'>
                                <Radio valor="E" name="EsteOeste" etiqueta='Este' onSelect={actualizarEsteOeste} />
                                <Radio valor="W" name="EsteOeste" etiqueta='Oeste' onSelect={actualizarEsteOeste} />
                            </div>
                        </div>

                    </div>
                    <div>
                        <h2 className='apartado'>Fecha y Hora</h2>
                        <div className="linea">
                            <InputHoraUTC label={'Hora UTC'} onChange={actualizarHora} />
                            <DatePicker label={"Fecha"} onChange={actualizarFecha} />
                        </div>
                    </div>
                    <div className='linea botones'> 
                        <button className='boton botonSecundario'>Borrar</button>
                        <button className='boton botonPrimario'>Calcular</button>
                    </div>
                </div>
            </form>
        </>
    )
}

function InputNumber({ label, onChange }) {
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
        <div className='inputContainer'>
            <label>{label}</label>
            <input type="number" className='input' value={valor} min="0" placeholder="0" onChange={handleChange}></input>
        </div>
    )
}

function InputHoraUTC({ label, onChange }) {
    const [valor, setValor] = useState('')
    const handleChange = (event) => {
        if (!isNaN(event.target.value) && event.target.value !== '') {
            if (event.target.value > 12) {
                setValor(12)
                onChange(parseInt(event.target.value))

            }
            else if (event.target.value < -11) {
                setValor(-11)
                onChange(parseInt(event.target.value))

            }
            else {
                setValor(event.target.value)
                onChange(parseInt(event.target.value))
            }

        }
        else if (event.target.value === '') {
            setValor('')
            onChange(0)
        }
    }

    return (
        <div className='inputContainer'>
            <label>{label}</label>
            <input className='input' placeholder='0' value={valor} type="number" onChange={handleChange} min="-11" max="12"></input>
        </div>
    )
}

function DatePicker({ label, onChange }) {
    const [valor, setValor] = useState('')
    const maxDate = "2020-12-31"
    const minDate = "2010-01-01"

    const handleChange = (event) => {
        if (event.target.value > event.target.max) {
            setValor(maxDate)
            onChange(maxDate)
        }
        else {
            setValor(event.target.value)
            onChange(event.target.value)
        }

    }

    return (
    <div className='inputContainer'>
        <label>{label}</label>
        <input className='input datepicker' type="date" max={maxDate} min={minDate} value={valor} onChange={handleChange} />
    </div>
    )
}

function Radio({ name, valor, onSelect, etiqueta }) {
    const handleSelect = (event) => {
        if (name === 'NorteSur') {
            if (valor === 'Norte') {
                onSelect(N)
            }
            else if (valor === 'Sur') {
                onSelect(S)
            }
        }
        else if (name === 'EsteOeste') {
            if (valor === 'Este') {
                onSelect(E)
            }
            else if (valor === 'Oeste') {
                onSelect(W)
            }
        }
    }

    return (
        <div className='radio'>
            <input type="radio" name={name} value={valor} onSelect={handleSelect} />
            <label htmlFor={name}>{etiqueta}</label>
        </div>
    )
}