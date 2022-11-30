import './Formulario.css'

export default function Formulario(props) {
    return (
        <div className="formulario">
            <h1 className='titulo'>Fenómenos de Sol para una fecha</h1>
            <form>
                <div className='apartado'>
                    <h2 className='posicion'>Posición</h2>
                    <div className='elementos'>
                        <Input label="Latitud" />
                        <Input label="Grados" />
                        <Input label="Minutos" />
                        <div>
                            <label className='inputLabel'>Orientación</label>
                            <div className='radioGroup'>
                                <Radio valor="Norte" name="Nortesur" />
                                <Radio valor="Sur" name="Nortesur" />
                            </div>
                        </div>
                    </div>

                </div>
            </form>
        </div>
    )
}
function Input(props) {
    return (
        <div>
            <label className='inputLabel'>{props.label}</label>
            <input className='input' placeholder="0"></input>
        </div>
    )
}

function Radio(props) {
    return (
        <div className='radioContainer'>
            <input type="radio" name={props.name} value={props.valor} />
            <label for={props.name}>{props.valor}</label>
        </div>
    )
}