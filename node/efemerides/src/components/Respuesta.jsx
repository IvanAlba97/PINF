export default function respuesta({ datos }) {
  let tabla = datos.tabla1;
  console.log(datos);
  if (datos.ERROR) {
    return <h1>Error: {datos.ERROR}</h1>;
  }
  if(datos.Sol)
  {
    let Sol = datos.Sol;
    let Fenomenos = datos.fenomenoSol;

    if (Sol.sinFenomeno != undefined) {
      return <h1>Sin Fenomeno : {Sol.sinFenomeno}</h1>;
    }
    return (
      <div>
        <div>Dia: {tabla.diai}</div>
        <div>Mes: {tabla.mesi}</div>
        <div>Año: {tabla.anoi}</div>
        <div>Hora: {tabla.horut}</div>
        <h2>Latitud</h2>
        <div>Grados: {tabla.latgra}</div>
        <div>Minutos: {tabla.minutos_lat}</div>
        <div>Orientación: {tabla.latsig}</div>
        <h2>Longitud</h2>
        <div>Grados:{tabla.longra}</div>
        <div>Minutos:{tabla.minutos_lon}</div>
        <div>Orientacion:{tabla.lonsig}</div>
  
        <h2>Sol</h2>
        <div>Culminacion: {Sol.culminacion}</div>
        <div>Grados Altura Sol: {Sol.gAlturaSol}</div>
        <div>Minutos Altura Sol: {Sol.mAlturaSol}</div>
        <div>Hora Paso Meridiano: {Sol.hPasoMeridiano}</div>
        <div>Minutos Paso Meridiano: {Sol.mPasoMeridiano}</div>
  
        <h1>Fenómenos</h1>
        <h2>Principio Crepúsculo Náutico</h2>
        <div>Hora: {Fenomenos.principioCrepNautico.hora1}</div>
        <div>Minutos: {Fenomenos.principioCrepNautico.minutos1}</div>
  
        <h2>Fin Crepúsculo Náutico</h2>
        <div>Hora: {Fenomenos.finCrepNautico.hora1}</div>
        <div>Minutos: {Fenomenos.finCrepNautico.minutos1}</div>
  
        <h2>Principio Crepúsculo Civil</h2>
        <div>Hora: {Fenomenos.principioCrepCivil.hora1}</div>
        <div>Minutos: {Fenomenos.principioCrepCivil.minutos1}</div>
  
        <h2>Fin Crepúsculo Civil</h2>
        <div>Hora: {Fenomenos.finCrepCivil.hora1}</div>
        <div>Minutos: {Fenomenos.finCrepCivil.minutos1}</div>
  
        <h2>Salida</h2>
        <div>Hora: {Fenomenos.salida.hora1}</div>
        <div>Minutos: {Fenomenos.salida.minutos1}</div>
  
        <h2>Puesta</h2>
        <div>Hora: {Fenomenos.puesta.hora1}</div>
        <div>Minutos: {Fenomenos.puesta.minutos1}</div>
  
        <h2>Acimutes</h2>
        <div>Grados Salida Superior: {Fenomenos.Acimutes.gSalidaSuperior}</div>
        <div>Minutos Salida Superior: {Fenomenos.Acimutes.mASalidaSuperior}</div>
        <div>Hora Salida Superior: {Fenomenos.Acimutes.hSalidaSuperior}</div>
        <div>
          Minutos (Tiempo) Salida Superior: {Fenomenos.Acimutes.mTSalidaSuperior}
        </div>
  
        <div>Grados Salida Inferior: {Fenomenos.Acimutes.gSalidaInferior}</div>
        <div>Minutos Salida Inferior: {Fenomenos.Acimutes.mASalidaInferior}</div>
        <div>Hora Salida Inferior: {Fenomenos.Acimutes.hSalidaInferior}</div>
        <div>
          Minutos (Tiempo) Salida Inferior: {Fenomenos.Acimutes.mTSalidaInferior}
        </div>
  
        <div>Grados Puesta Superior: {Fenomenos.Acimutes.gPuestaSuperior}</div>
        <div>Minutos Puesta Superior: {Fenomenos.Acimutes.mAPuestaSuperior}</div>
        <div>Hora Salida Superior: {Fenomenos.Acimutes.hSalidaSuperior}</div>
        <div>
          Minutos (Tiempo) Salida Superior: {Fenomenos.Acimutes.mTSalidaSuperior}
        </div>
  
        <div>Grados Puesta Inferior: {Fenomenos.Acimutes.gPuestaInferior}</div>
        <div>Minutos Puesta Inferior: {Fenomenos.Acimutes.mAPuestaInferior}</div>
        <div>Hora Salida Inferior: {Fenomenos.Acimutes.hSalidaInferior}</div>
        <div>
          Minutos (Tiempo) Salida Inferior: {Fenomenos.Acimutes.mTSalidaInferior}
        </div>
      </div>
    );
  }
  else if(datos.Luna)
  {
    return <h1>Respuesta de Luna</h1>
  }
}
