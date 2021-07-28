import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import App from './App';
import reportWebVitals from './reportWebVitals';
import { firebase } from '@firebase/app';

require("firebase/database");



const firebaseConfig = {
  apiKey: "AIzaSyBD4DRtVqGypWQcF8L4dYgkmQW0oM1rx80",
  authDomain: "esp32-projects-6132f.firebaseapp.com",
  databaseURL: "https://esp32-projects-6132f-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "esp32-projects-6132f",
  storageBucket: "esp32-projects-6132f.appspot.com",
  messagingSenderId: "902593767844",
  appId: "1:902593767844:web:dd351f21b61c675792f931"
};

firebase.initializeApp(firebaseConfig);
console.log("%cIcons credit to https://icon54.com/ and https://www.freepik.com", "color:blue");

console.log('%c Heyyo!!', 'font-weight: bold; font-size: 50px;color: red; text-shadow: 3px 3px 0 rgb(217,31,38) , 6px 6px 0 rgb(226,91,14) , 9px 9px 0 rgb(245,221,8) , 12px 12px 0 rgb(5,148,68) , 21px 21px 0 rgb(42,21,113)');

ReactDOM.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
  document.getElementById('root')
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
