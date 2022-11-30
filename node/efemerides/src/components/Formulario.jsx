import './Formulario.css'

export default function Formulario(tipo) {
    return (
        <div className="formulario">
            <h1 className='titulo'>Fenómenos de Sol para una fecha</h1>
            <form>
                <input placeholder="0"></input>
                <input placeholder="0"></input>
                <input placeholder="0"></input>
            </form>
        </div>
    )
}