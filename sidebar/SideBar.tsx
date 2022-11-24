import { useState } from "react";

export default function SideBar() {
  const tipos = [
    "sol",
    "Luna",
    "Eclipses de Sol y Luna",
    "Ocultaciones",
    "Miscelanea",
  ];
  const [s, Sets] = useState(-1);

  const listItems = tipos.map((tipo, key) => (
    <div className="flex">
      {key == s ? (
        <p className="text-Sel text-normal text-2xl mr-2">|</p>
      ) : null}
      <button
        onClick={() => Sets(key)}
        className={
          "text-normal text-2xl hover:text-Sel " +
          (key == s ? "text-Sel" : "text-noSel")
        }
      >
        {tipo}
      </button>
    </div>
  ));

  return (
    <div className="h-fit xl:h-screen bg-blueS space-y-11 px-12 pt-20">
      <h1 className="text-Sel font-bold text-5xl">Efemérides</h1>
      <div className="space-y-14 flex-col sm:flex">{listItems}</div>
    </div>
  );
}
