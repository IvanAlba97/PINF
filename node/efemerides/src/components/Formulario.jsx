import { useState, useEffect } from 'react'
import './Formulario.css'
import './Spinner.css'

export default function Formulario({ nombre, enlace, }) {

    const estadoInicial = {
        gradosLat: '',
        minutosLat: '',
        segundosLat: '',
        segundosLong: '',
        gradosLong: '',
        minutosLong: '',
        fecha: '',
        hora: '',
        norteSur: '', // 0 Norte, 1 Sur
        esteOeste: '', //0 Este, 1 Oeste

    }
    const [datos, setDatos] = useState(
        estadoInicial
    )

    const [loading, setLoading] = useState(false)
    const [respuesta, setRespuesta] = useState(undefined)

    useEffect(() => {
        if (loading)
            setLoading(false)
        if (respuesta)
            setRespuesta(null)
    }, [nombre])
    async function fetchingData() {
        const fecha = new Date(datos.fecha)
        const dia = fecha.getDate()
        const mes = fecha.getMonth() + 1
        const año = fecha.getFullYear()
        let url = `http://192.168.0.8/cgi-bin/enfecha.cgi?latgra=${datos.gradosLat}&latmin=${datos.minutosLat}&latseg=${datos.segundosLat}&latsig=${datos.norteSur}&longra=${datos.gradosLong}&lonmin=${datos.minutosLong}&lonseg=${datos.segundosLong}&lonsig=${datos.esteOeste}&horut=${datos.hora}&anoi=${año}&mesi=${mes}&diai=${dia}`
        let resultado = await fetch(url)
        resultado = await resultado.json()
        return resultado;
    }

    const handleSubmit = (event) => {
        event.preventDefault()
        setLoading(true)
        fetchingData().then((res) => {
            setRespuesta(res)
            setLoading(false)
        }).catch((err) => { setLoading(false) })
    }

    const handleBorrar = () => { setDatos(estadoInicial) }
    const actualizarGradosLat = (estado) => { setDatos({ ...datos, gradosLat: estado }) }
    const actualizarMinutosLat = (estado) => { setDatos({ ...datos, minutosLat: estado }) }
    const actualizarSegundosLat = (estado) => { setDatos({ ...datos, segundosLat: estado }) }
    const actualizarGradosLong = (estado) => { setDatos({ ...datos, gradosLong: estado }) }
    const actualizarMinutosLong = (estado) => { setDatos({ ...datos, minutosLong: estado }) }
    const actualizarSegundosLong = (estado) => { setDatos({ ...datos, segundosLong: estado }) }
    const actualizarFecha = (estado) => { setDatos({ ...datos, fecha: estado }) }
    const actualizarHora = (estado) => { setDatos({ ...datos, hora: estado }) }
    const actualizarNorteSur = (estado) => {
        setDatos({ ...datos, norteSur: estado })
    }
    const actualizarEsteOeste = (estado) => {
        setDatos({ ...datos, esteOeste: estado })
    }

    if (loading) {
        return (<div className='spinner' />)
    }

    if (respuesta) {
        if (respuesta.ERROR) {
            return (
                <div className='error'>{respuesta.ERROR}</div>
            )
        } else {
            return (
                <table>
                    <thead>
                        <tr>
                            RESPUESTA
                        </tr>
                    </thead>
                </table>
            )
        }
    }

    return (
        <>
            <h1 className='titulo'>Fenómenos de {nombre} para una fecha</h1>
            <form className='formulario' onSubmit={handleSubmit} >
                <div>
                    <h2 className='apartado'>Posición</h2>
                    <h4 className='subapartado'>Latitud</h4>
                    <div className='linea'>
                        <InputNumber label="Grados" value={datos.gradosLat} onChange={actualizarGradosLat} />
                        <InputNumber label="Minutos" value={datos.minutosLat} onChange={actualizarMinutosLat} />
                        <InputNumber label="Segundos" value={datos.segundosLat} onChange={actualizarSegundosLat} />
                        <div className='radioGroup'>
                            <label className='radioLabel'>Orientación</label>
                            <div className='radioContainer'>
                                <Radio valor="N" name="NorteSur" dato={datos.norteSur} etiqueta='Norte' onSelect={actualizarNorteSur} />
                                <Radio valor="S" name="NorteSur" dato={datos.norteSur} etiqueta='Sur' onSelect={actualizarNorteSur} />
                            </div>
                        </div>
                    </div>

                    <h4 className='subapartado'>Longitud</h4>
                    <div className="linea">
                        <InputNumber label="Grados" value={datos.gradosLong} onChange={actualizarGradosLong} />
                        <InputNumber label="Minutos" value={datos.minutosLong} onChange={actualizarMinutosLong} />
                        <InputNumber label="Segundos" value={datos.segundosLong} onChange={actualizarSegundosLong} />
                        <div className='radioGroup'>
                            <label className='radioLabel'>Orientación</label>
                            <div className='radioContainer'>
                                <Radio valor="E" name="EsteOeste" etiqueta='Este' dato={datos.esteOeste} onSelect={actualizarEsteOeste} />
                                <Radio valor="W" name="EsteOeste" etiqueta='Oeste' dato={datos.esteOeste} onSelect={actualizarEsteOeste} />
                            </div>
                        </div>

                    </div>
                    <div>
                        <h2 className='apartado'>Fecha y Hora</h2>
                        <div className="linea">
                            <InputHoraUTC label={'Hora UTC'} onChange={actualizarHora} value={datos.hora} />
                            <DatePicker label={"Fecha"} onChange={actualizarFecha} value={datos.fecha} />
                        </div>
                    </div>
                    <div className='linea botones'>
                        <input type="reset" value='Borrar' className='boton botonSecundario' onClick={handleBorrar} />
                        <input type='submit' value='Calcular' className='boton botonPrimario'></input>
                    </div>
                </div>
            </form>
        </>
    )
}

function InputNumber({ label, onChange, value }) {

    const handleChange = (event) => {
        if (!isNaN(event.target.value) && event.target.value !== '') {
            onChange(parseInt(event.target.value))
        }
        else if (event.target.value === '') {
            onChange(0)
        }
    }

    return (
        <div className='inputContainer'>
            <label>{label}</label>
            <input type="number" className='input' value={value} min="0" placeholder="0" onChange={handleChange} required></input>
        </div>
    )
}

function InputHoraUTC({ label, onChange, value }) {

    const handleChange = (event) => {
        if (!isNaN(event.target.value) && event.target.value !== '') {
            if (event.target.value > 12) {
                onChange(12)
            }
            else if (event.target.value < -11) {
                onChange(-11)
            }
            else {
                onChange(parseInt(event.target.value))
            }
        }
        else if (event.target.value === '') {
            onChange(0)
        }
    }

    return (
        <div className='inputContainer'>
            <label>{label}</label>
            <input className='input' placeholder='0' value={value} type="number" onChange={handleChange} min="-11" max="12" required />
        </div>
    )
}

function DatePicker({ label, onChange, value }) {
    const maxDate = "2020-12-31"
    const minDate = "2010-01-01"

    const handleChange = (event) => {
        if (event.target.value > event.target.max) {
            onChange(maxDate)
        }
        else {
            onChange(event.target.value)
        }

    }

    return (
        <div className='inputContainer'>
            <label>{label}</label>
            <input className='input datepicker' type="date" max={maxDate} min={minDate} value={value} onChange={handleChange} required />
        </div>
    )
}

function Radio({ name, valor, dato, onSelect, etiqueta }) {
    const handleSelect = (event) => {
        onSelect(event.target.value)
    }

    return (
        <div className='radio'>
            <input type="radio" name={name} value={valor} onChange={handleSelect} checked={dato === valor} required />
            <label htmlFor={name}>{etiqueta}</label>
        </div>
    )
}