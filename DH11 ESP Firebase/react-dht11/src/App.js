import { firebase } from '@firebase/app';
import { FirebaseDatabaseNode } from '@react-firebase/database';
import React from 'react';
import './App.css';

function App() {
  return (
    <FirebaseDatabaseNode path="Bilik/" firebase={firebase}>
      {
        data => {
          const { value } = data;
          if (value === null || typeof value === "undefined") return null;
          const keys = Object.keys(value);
          const values = Object.values(value);
          const valuesWithKeys = values.map(
            (value, i) => ({
              type: value.type,
              value: value.value,
              updated: value.updated,
              id: keys[i]
            })
          );
          // console.log(valuesWithKeys);

          return <React.Fragment>

            <div className="time">
              Last updated: {valuesWithKeys[0].updated}
            </div>
            <div className="card">
              <img src={require('./assets/humidity.png').default} alt="icon" ></img>

              <div className="container">
                <h2>{valuesWithKeys[0].type} :</h2>
                <h1>{valuesWithKeys[0].value} RH</h1>

              </div>
            </div>
            <p></p>
            <div className="card">
              <img src={require('./assets/thermometer.png').default} alt="icon" ></img>

              <div className="container">

                <h2>{valuesWithKeys[1].type} :</h2>
                <h1>{valuesWithKeys[1].value.toFixed(1)} °C</h1>

              </div>
            </div>
            <div className="footer">
              Hi, maceh sbb mem-visit huhu. <a onClick={() => alert('MEOWZ AUMM')}>🐱</a>
            </div>

            <div className="info">
              Made by <a href="https://github.com/iqfareez" target=" _blank" rel="noreferrer">@iqfareez</a>. Powered by <a href="https://my.cytron.io/p-nodemcu-esp32" target="_blank" rel="noreferrer">ESP32</a> board and <a href="https://my.cytron.io/p-grove-temperature-and-humidity-sensor-dht11" target="_blank" rel="noreferrer">DHT11</a> sensor.
            </div>

          </React.Fragment>
        }
      }

    </FirebaseDatabaseNode >
  );
}

export default App;
