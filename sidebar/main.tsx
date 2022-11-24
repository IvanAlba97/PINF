import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App'
import './index.css'
import SideBar from "./SideBar";


ReactDOM.createRoot(document.getElementById("root") as HTMLElement).render(
  <React.StrictMode>
    <div className="xl:flex sm:flex-1 h-screen w-screen">
      <aside className="w-4/12 xl:w-4/12 sm:w-full">
        <SideBar />
      </aside>
      <main className="w-full">
        <App />
      </main>
    </div>
  </React.StrictMode>
);
