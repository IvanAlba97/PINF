import { useState, useEffect, useRef } from 'react';
import Respuesta from './Respuesta';
import './Formulario.css';
import './Spinner.css';

export default function Formulario({ nombre, enlace }) {
  console.ignoreRedBox = true;
  const estadoInicial = {
    gradosLat: NaN,
    minutosLat: NaN,
    segundosLat: NaN,
    segundosLong: NaN,
    gradosLong: NaN,
    minutosLong: NaN,
    fecha: '',
    fechaF: '',
    hora: '',
    norteSur: '', // 0 Norte, 1 Sur
    esteOeste: '', //0 Este, 1 Oeste
  };

  const [datos, setDatos] = useState(estadoInicial);

  const [intervalo, setIntervalo] = useState(false);
  const [loading, setLoading] = useState(false);
  const [respuesta, setRespuesta] = useState(undefined);

  useEffect(() => {
    if (loading) setLoading(false);
    if (respuesta) setRespuesta(null);
  }, [nombre]);

  async function fetchingData() {
    const fecha = new Date(datos.fecha);
    const dia = fecha.getDate();
    const mes = fecha.getMonth() + 1;
    const año = fecha.getFullYear();

    const fechaF = new Date(datos.fechaF);
    const diaf = fechaF.getDate();
    const mesf = fechaF.getMonth() + 1;
    const añof = fechaF.getFullYear();
    let url;
    const ip = "10.41.0.13"
    console.log(nombre);
    if (!intervalo) {
      if (nombre === 'sol') {
        url = `http://${ip}/cgi-bin/enfecha.cgi?latgra=${datos.gradosLat}&latmin=${datos.minutosLat}&latseg=${datos.segundosLat}&latsig=${datos.norteSur}&longra=${datos.gradosLong}&lonmin=${datos.minutosLong}&lonseg=${datos.segundosLong}&lonsig=${datos.esteOeste}&horut=${datos.hora}&anoi=${año}&mesi=${mes}&diai=${dia}`;
      } else if (nombre === 'luna') {
        url = `http://${ip}/cgi-bin/enfechaluna.cgi?latgra=${datos.gradosLat}&latmin=${datos.minutosLat}&latseg=${datos.segundosLat}&latsig=${datos.norteSur}&longra=${datos.gradosLong}&lonmin=${datos.minutosLong}&lonseg=${datos.segundosLong}&lonsig=${datos.esteOeste}&horut=${datos.hora}&anoi=${año}&mesi=${mes}&diai=${dia}`;
      }
    } else {
      if (nombre === 'sol') {
        console.log('Dentro');
        url = `http://${ip}/cgi-bin/andi.cgi?latgra=${datos.gradosLat}&latmin=${datos.minutosLat}&latseg=${datos.segundosLat}&latsig=${datos.norteSur}&longra=${datos.gradosLong}&lonmin=${datos.minutosLong}&lonseg=${datos.segundosLong}&lonsig=${datos.esteOeste}&horut=${datos.hora}&anoi=${año}&mesi=${mes}&diai=${dia}&anof=${añof}&mesf=${mesf}&diaf=${diaf}`;
      } else if (nombre === 'luna') {
        url = `http://${ip}/cgi-bin/andiluna.cgi?latgra=${datos.gradosLat}&latmin=${datos.minutosLat}&latseg=${datos.segundosLat}&latsig=${datos.norteSur}&longra=${datos.gradosLong}&lonmin=${datos.minutosLong}&lonseg=${datos.segundosLong}&lonsig=${datos.esteOeste}&horut=${datos.hora}&anoi=${año}&mesi=${mes}&diai=${dia}&anof=${añof}&mesf=${mesf}&diaf=${diaf}`;
      }
    }
    console.log(url);
    let resultado = await fetch(url);
    resultado = await resultado.json();
    return resultado;
  }

  const handleSubmit = (event) => {
    event.preventDefault();
    setLoading(true);
    fetchingData()
      .then((res) => {
        setRespuesta(res);
        setLoading(false);
      })
      .catch((err) => {
        setLoading(false);
        setIntervalo(false);
      });
  };

  const handleBorrar = () => {
    setIntervalo(false);
    setDatos(estadoInicial);
  };
  const actualizarGradosLat = (estado) => {
    setDatos({ ...datos, gradosLat: estado });
  };
  const actualizarMinutosLat = (estado) => {
    setDatos({ ...datos, minutosLat: estado });
  };
  const actualizarSegundosLat = (estado) => {
    setDatos({ ...datos, segundosLat: estado });
  };
  const actualizarGradosLong = (estado) => {
    setDatos({ ...datos, gradosLong: estado });
  };
  const actualizarMinutosLong = (estado) => {
    setDatos({ ...datos, minutosLong: estado });
  };
  const actualizarSegundosLong = (estado) => {
    setDatos({ ...datos, segundosLong: estado });
  };
  const actualizarFecha = (estado) => {
    setDatos({ ...datos, fecha: estado });
  };
  const actualizarFechaF = (estado) => {
    setDatos({ ...datos, fechaF: estado });
  };
  const actualizarHora = (estado) => {
    setDatos({ ...datos, hora: estado });
  };
  const actualizarNorteSur = (estado) => {
    setDatos({ ...datos, norteSur: estado });
  };
  const actualizarEsteOeste = (estado) => {
    setDatos({ ...datos, esteOeste: estado });
  };

  if (loading) {
    return <div className='spinner' />;
  }

  if (respuesta) {
    return <Respuesta datos={respuesta} intervalo={intervalo} />;
  }

  function Fecha() {
    if (!intervalo) {
      return (
          <DatePicker
            label={'Fecha'}
            onChange={actualizarFecha}
            value={datos.fecha}
          />
      );
    } else {
      return (
        <>
            <DatePicker
              label={'Fecha inicial'}
              onChange={actualizarFecha}
              value={datos.fecha}
            />
            <DatePicker
              label={'Fecha final'}
              onChange={actualizarFechaF}
              value={datos.fechaF}
            />
        </>
      );
    }
  }

  return (
    <>
      <h1 className='titulo'>Fenómenos de {nombre} para una fecha</h1>
      <form className='formulario' onSubmit={handleSubmit}>
        <div>
          <h2 className='apartado'>Posición</h2>
          <h4 className='subapartado'>Latitud</h4>
          <div className='linea'>
            <InputNumber
              label='Grados'
              value={datos.gradosLat}
              max={90}
              min={0}
              onChange={actualizarGradosLat}
            />
            <InputNumber
              label='Minutos'
              value={datos.minutosLat}
              onChange={actualizarMinutosLat}
              max={60}

            />
            <InputNumber
              label='Segundos'
              value={datos.segundosLat}
              onChange={actualizarSegundosLat}
              max={60}

            />
            <div className='radioGroup'>
              <label className='radioLabel'>Orientación</label>
              <div className='radioContainer'>
                <Radio
                  valor='N'
                  name='NorteSur'
                  dato={datos.norteSur}
                  etiqueta='Norte'
                  onSelect={actualizarNorteSur}
                />
                <Radio
                  valor='S'
                  name='NorteSur'
                  dato={datos.norteSur}
                  etiqueta='Sur'
                  onSelect={actualizarNorteSur}
                />
              </div>
            </div>
          </div>

          <h4 className='subapartado'>Longitud</h4>
          <div className='linea'>
            <InputNumber
              label='Grados'
              value={datos.gradosLong}
              onChange={actualizarGradosLong}
              max={90}

            />
            <InputNumber
              label='Minutos'
              value={datos.minutosLong}
              onChange={actualizarMinutosLong}
              max={60}

            />
            <InputNumber
              label='Segundos'
              value={datos.segundosLong}
              onChange={actualizarSegundosLong}
              max={60}
              
            />
            <div className='radioGroup'>
              <label className='radioLabel'>Orientación</label>
              <div className='radioContainer'>
                <Radio
                  valor='E'
                  name='EsteOeste'
                  etiqueta='Este'
                  dato={datos.esteOeste}
                  onSelect={actualizarEsteOeste}
                />
                <Radio
                  valor='W'
                  name='EsteOeste'
                  etiqueta='Oeste'
                  dato={datos.esteOeste}
                  onSelect={actualizarEsteOeste}
                />
              </div>
            </div>
          </div>
          <div>
            <h2 className='apartado'>Tiempo</h2>
            <div className='checkbox'>
              <input
                onChange={() => setIntervalo(!intervalo)}
                type='checkbox'
                checked={intervalo}
              ></input>
              <label>Intervalo</label>
            </div>
            <div className='linea'>
              <Fecha />
              <InputHoraUTC
                onChange={actualizarHora}
                value={datos.hora}
                label='Hora UTC'
              />
            </div>
          </div>
          <div className='linea botones'>
            <input
              type='reset'
              value='Borrar'
              className='boton botonSecundario'
              onClick={handleBorrar}
            />
            <input
              type='submit'
              value='Calcular'
              className='boton botonPrimario'
            ></input>
          </div>
        </div>
      </form>
    </>
  );
}

function InputNumber({ label, onChange, value, max }) {
  const handleChange = (event) => {
    if (!isNaN(parseInt(event.target.value))) {
      if (event.target.value > max) {
        onChange(max);
      }
      onChange(parseInt(event.target.value));
    } else if (event.target.value == '') {
      onChange(NaN);
    }
  };

  return (
    <div className='inputContainer'>
      <label>{label}</label>
      <input
        className='input'
        type='number'
        value={value}
        min='0'
        max={max}
        placeholder='0'
        onChange={handleChange}
        required
      ></input>
    </div>
  );
}

function InputHoraUTC({ label, onChange, value }) {
  const handleChange = (event) => {
    if (!isNaN(parseInt(event.target.value))) {
      onChange(parseInt(event.target.value));
    }
  };

  let horas = [
    '--',
    -11,
    -10,
    -9,
    -8,
    -7,
    -6,
    -5,
    -4,
    -3,
    -2,
    -1,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
  ];
  return (
    <div className='inputContainer'>
      <label>{label}</label>
      <select
        className='input'
        type='select'
        placeholder='0'
        value={value}
        onChange={handleChange}
      >
        {horas.map((valor) => {
          return (
            <option key={valor} value={valor}>
              {valor}
            </option>
          );
        })}
      </select>
    </div>
  );
}

function DatePicker({ label, onChange, value }) {
  const maxDate = '2020-12-31';
  const minDate = '2010-01-01';

  const handleChange = (event) => {
    if (event.target.value > event.target.max) {
      onChange(maxDate);
    } else {
      onChange(event.target.value);
    }
  };

  return (
    <div className='inputContainer'>
      <label>{label}</label>
      <input
        className='input datepicker'
        type='date'
        max={maxDate}
        min={minDate}
        value={value}
        onChange={handleChange}
        required
      />
    </div>
  );
}

function Radio({ name, valor, dato, onSelect, etiqueta }) {
  const handleSelect = (event) => {
    onSelect(event.target.value);
  };

  return (
    <div className='radio'>
      <input
        type='radio'
        name={name}
        value={valor}
        onChange={handleSelect}
        checked={dato === valor}
        required
      />
      <label htmlFor={name}>{etiqueta}</label>
    </div>
  );
}
