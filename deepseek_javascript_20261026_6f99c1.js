import React, { useState, useEffect } from 'react';

function App() {
  const [data, setData] = useState({ flow: 0, c3_index: 0, status: 'Loading' });

  useEffect(() => {
    const interval = setInterval(() => {
      fetch('http://localhost:5000/api/status')
        .then(res => res.json())
        .then(d => setData(d))
        .catch(err => console.log("Error fetching data"));
    }, 2000);
    return () => clearInterval(interval);
  }, []);

  return (
    <div style={{ backgroundColor: '#0a0a1a', color: 'white', height: '100vh', padding: '50px', fontFamily: 'sans-serif' }}>
      <h1>🇮🇳 भारत Rakshak - Autonomous Defense Grid</h1>
      <h2>Status: <span style={{ color: data.status === 'ATTACK' ? 'red' : '#00ff88' }}>{data.status}</span></h2>
      
      <div style={{ display: 'flex', gap: '20px', marginTop: '30px' }}>
        <div style={{ border: '1px solid #00ff88', padding: '20px', borderRadius: '10px' }}>
          <h3>Water Flow</h3>
          <p>{data.flow} L/min</p>
        </div>
        <div style={{ border: '1px solid #00ff88', padding: '20px', borderRadius: '10px' }}>
          <h3>C3-Index</h3>
          <p>{data.c3_index}</p>
        </div>
        <div style={{ border: '1px solid #00ff88', padding: '20px', borderRadius: '10px' }}>
          <h3>Water Saved</h3>
          <p>{data.water_saved} L</p>
        </div>
      </div>
    </div>
  );
}

export default App;