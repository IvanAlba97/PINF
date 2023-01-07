import './Respuesta.css'

export default function Respuesta({ datos, intervalo }) {
  let tabla = datos.tabla1;

  if (datos.ERROR) {
    return (
      <div id="contenedor">
         {/* <div className="fecha">
          Fecha: {tabla.diai}/{tabla.mesi}/{tabla.anoi}
        </div>
        <table id="coordenadas">
          <tr>
            <th id="header">Hora-UT</th>
            <td>{tabla.horut}h</td>
          </tr>
          <tr>
            <th id="header">Latitud</th>
            <td>
              {tabla.latgra}º {tabla.minutos_lat}' {tabla.latsig}
            </td>
          </tr>
          <tr>
            <th id="header">Longitud</th>
            <td>
              {tabla.longra}º {tabla.minutos_lon}' {tabla.lonsig}
            </td>
          </tr>
        </table>  */}
        <h1 className="ERROR">{datos.ERROR}</h1>
      </div>
    );
  }
  if (intervalo) {
    let interval = datos.DatosFecha;
    console.log(interval);

    if (interval[0].SalidaLimboSuperior) {
      return (
        <div id="contenedor">
          <div className="fecha">
            Intervalo: {datos.diaI}/{datos.mesI}/{datos.anoI} - {datos.diaF}/
            {datos.mesF}/{datos.anoF}
          </div>
          <table id="coordenadas">
            <tr>
              <th id="header">Hora-UT</th>
              <td>{tabla.horut}h</td>
            </tr>
            <tr>
              <th id="header">Latitud</th>
              <td>
                {tabla.latgra}º {tabla.minutos_lat}' {tabla.latsig}
              </td>
            </tr>
            <tr>
              <th id="header">Longitud</th>
              <td>
                {tabla.longra}º {tabla.minutos_lon}' {tabla.lonsig}
              </td>
            </tr>
          </table>

          <table className="intervalo">
            <tr>
              <th id="header"></th>
              <th id="header">Orto</th>
              <th id="header">Meridiano</th>
              <th id="header">Ocaso</th>
            </tr>
            {interval.map((dia) => (
              <tr>
                <th>
                  {dia.dia}/{dia.mes}/{dia.ano}
                </th>
                <td>
                  {dia.SalidaLimboSuperior.hora}:
                  {dia.SalidaLimboSuperior.minutos}h
                </td>
                <td>
                  {dia.PasoMeridiano.hora}:{dia.PasoMeridiano.minutos}h
                </td>
                <td>
                  {dia.PuestaLimboSuperior.hora}:
                  {dia.PuestaLimboSuperior.minutos}h
                </td>
              </tr>
            ))}
          </table>
        </div>
      );
    } else if (interval[0].Salida) {
      return (
        <div id="contenedor">
          <div className="fecha">
            Intervalo: {datos.diaI}/{datos.mesI}/{datos.anoI} - {datos.diaF}/
            {datos.mesF}/{datos.anoF}
          </div>
          <table id="coordenadas">
            <tr>
              <th id="header">Hora-UT</th>
              <td>{tabla.horut}h</td>
            </tr>
            <tr>
              <th id="header">Latitud</th>
              <td>
                {tabla.latgra}º {tabla.minutos_lat}' {tabla.latsig}
              </td>
            </tr>
            <tr>
              <th id="header">Longitud</th>
              <td>
                {tabla.longra}º {tabla.minutos_lon}' {tabla.lonsig}
              </td>
            </tr>
          </table>

          <table className="intervalo">
            <tr>
              <th id="header"></th>
              <th id="header">Orto</th>
              <th id="header">Meridiano</th>
              <th id="header">Ocaso</th>
              <th id="header">Edad</th>
            </tr>
            {interval.map((dia) => (
              <tr>
                <th>
                  {dia.dia}/{dia.mes}/{dia.ano}
                </th>
                <td>
                  {dia.Salida.hora || dia.Salida.minutos
                    ? dia.Salida.hora + ":" + dia.Salida.minutos + "h"
                    : "----"}
                </td>
                <td>
                  {dia.PasoMeridiano.hora || dia.PasoMeridiano.minutos
                    ? dia.PasoMeridiano.hora +
                      ":" +
                      dia.PasoMeridiano.minutos +
                      "h"
                    : "----"}
                </td>
                <td>
                  {dia.Puesta.hora || dia.Puesta.minutos
                    ? dia.Puesta.hora + ":" + dia.Puesta.minutos + "h"
                    : "----"}
                </td>
                <td>{dia.edad}</td>
              </tr>
            ))}
          </table>
        </div>
      );
    }
  }

  
  if (datos.Sol) {
    let Sol = datos.Sol;
    let Fenomenos = datos.fenomenoSol;

    if (Sol.sinFenomeno != undefined) {
      return <h1>Sin Fenomeno : {Sol.sinFenomeno}</h1>;
    }
    return (
      <div id="contenedor">
        <div className="fecha">
          Fecha: {tabla.diai}/{tabla.mesi}/{tabla.anoi}
        </div>
        <table id="coordenadas">
          <tr>
            <th id="header">Hora-UT</th>
            <td>{tabla.horut}h</td>
          </tr>
          <tr>
            <th id="header">Latitud</th>
            <td>
              {tabla.latgra}º {tabla.minutos_lat}' {tabla.latsig}
            </td>
          </tr>
          <tr>
            <th id="header">Longitud</th>
            <td>
              {tabla.longra}º {tabla.minutos_lon}' {tabla.lonsig}
            </td>
          </tr>
        </table>

        <table id="Sol">
          <tr>
            <th id="header">Culminacion</th>
            <td>{Sol.culminacion}</td>
          </tr>
          <tr>
            <th id="header">Grados Altura Sol</th>
            <td>
              {Sol.gAlturaSol}º {Sol.mAlturaSol}'
            </td>
          </tr>
          <tr>
            <th id="header">Hora Paso Meridiano</th>
            <td>
              {Sol.hPasoMeridiano}:{Sol.mPasoMeridiano}h
            </td>
          </tr>
        </table>

        <table id="Fenomenos">
          <tr>
            <th>Fenómenos</th>
          </tr>
          <tr>
            <table>
              <th></th>
              <th>inicio</th>
              <th>final</th>
              <tr>
                <th id="header">Crepúsculo Civil</th>
                <td>
                  {Fenomenos.principioCrepCivil.hora1}:
                  {Fenomenos.principioCrepCivil.minutos1}h
                </td>
                <td>
                  {Fenomenos.finCrepCivil.hora1}:
                  {Fenomenos.finCrepCivil.minutos1}h
                </td>
              </tr>
              <tr>
                <th id="header">Crepúsculo Nautico</th>
                <td>
                  {Fenomenos.principioCrepNautico.hora1}:
                  {Fenomenos.principioCrepNautico.minutos1}h
                </td>
                <td>
                  {Fenomenos.finCrepNautico.hora1}:
                  {Fenomenos.finCrepNautico.minutos1}h
                </td>
              </tr>
              <tr>
                <th id="header">Salida/Puesta</th>
                <td>
                  {Fenomenos.salida.hora1}:{Fenomenos.salida.minutos1}h
                </td>
                <td>
                  {Fenomenos.puesta.hora1}:{Fenomenos.puesta.minutos1}h
                </td>
              </tr>
            </table>
          </tr>
        </table>

        <table id="acimutes">
          <tr>
            <th>Acimutes</th>
          </tr>
          <table>
            <tr>
              <th></th>
              <th>Superior</th>
              <th>Inferior</th>
            </tr>
            <tr>
              <th id="header">Salida</th>
              <td>
                <table id="doble">
                  <td>
                    {Fenomenos.Acimutes.gSalidaSuperior}º{" "}
                    {Fenomenos.Acimutes.mASalidaSuperior}'
                  </td>
                  <td>
                    {Fenomenos.Acimutes.hSalidaSuperior}:
                    {Fenomenos.Acimutes.mTSalidaSuperior}h
                  </td>
                </table>
              </td>
              <td>
                <table id="doble">
                  <td>
                    {Fenomenos.Acimutes.gSalidaInferior}º{" "}
                    {Fenomenos.Acimutes.mASalidaInferior}'
                  </td>
                  <td>
                    {Fenomenos.Acimutes.hSalidaInferior}:
                    {Fenomenos.Acimutes.mTSalidaInferior}h
                  </td>
                </table>
              </td>
            </tr>
            <tr>
              <th id="header">Puesta</th>
              <td>
                <table id="doble">
                  <td>
                    {Fenomenos.Acimutes.gPuestaSuperior}º{" "}
                    {Fenomenos.Acimutes.mAPuestaSuperior}'
                  </td>
                  <td>
                    {Fenomenos.Acimutes.hPuestaSuperior}:
                    {Fenomenos.Acimutes.mTPuestaSuperior}h
                  </td>
                </table>
              </td>
              <td>
                <table id="doble">
                  <td>
                    {Fenomenos.Acimutes.gPuestaInferior}º{" "}
                    {Fenomenos.Acimutes.mAPuestaInferior}'
                  </td>
                  <td>
                    {Fenomenos.Acimutes.hPuestaInferior}:
                    {Fenomenos.Acimutes.mTPuestaInferior}h
                  </td>
                </table>
              </td>
            </tr>
          </table>
        </table>
      </div>
    );
  } else if (datos.Luna) {
    let Luna = datos.Luna;
    return (
      <div id="contenedor">
        <div className="fecha">
          Fecha: {tabla.diai}/{tabla.mesi}/{tabla.anoi}
        </div>
        <table id="coordenadas">
          <tr>
            <th id="header">Hora-UT</th>
            <td>{tabla.horut}h</td>
          </tr>
          <tr>
            <th id="header">Edad (a 0h)</th>
            <td>{Luna.edad0h}</td>
          </tr>
          <tr>
            <th id="header">Latitud</th>
            <td>
              {tabla.latgra}º {tabla.minutos_lat}' {tabla.latsig}
            </td>
          </tr>
          <tr>
            <th id="header">Longitud</th>
            <td>
              {tabla.longra}º {tabla.minutos_lon}' {tabla.lonsig}
            </td>
          </tr>
        </table>

        <table id="Luna">
          <tr>
            <th id="header">Culminacion</th>
            <td>{Luna.culminacion}</td>
          </tr>
          <tr>
            <th id="header">Grados Altura Luna</th>
            <td>
              {Luna.gAlturaMeridiano}º {Luna.mAlturaMeridiano}'
            </td>
          </tr>
          <tr>
            <th id="header">Hora Paso Meridiano</th>
            <td>
              {Luna.hPasoMeridiano}:{Luna.mPasoMeridiano}h
            </td>
          </tr>
        </table>

        <table id="acimutes">
          <tr>
            <th></th>
            <th>Grados</th>
            <th>Hora</th>
          </tr>
          <tr>
            <th id="header">Salida</th>
            <td>
              {datos.Acimutes.gAcimutSalida}º {datos.Acimutes.mAcimutSalida}'
            </td>
            <td>
              {datos.Acimutes.hSalida}:{datos.Acimutes.mSalida}h
            </td>
          </tr>
          <tr>
            <th id="header">Puesta</th>
            <td>
              {datos.Acimutes.gAcimutPuesta}º {datos.Acimutes.mAcimutPuesta}'
            </td>
            <td>
              {datos.Acimutes.hPuesta}:{datos.Acimutes.mPuesta}h
            </td>
          </tr>
        </table>
      </div>
    );
  }
}
