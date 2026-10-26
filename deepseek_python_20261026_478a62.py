from flask import Flask, jsonify
import random
from c3_index import C3IndexCalculator

app = Flask(__name__)
c3_calc = C3IndexCalculator()

@app.route('/api/status')
def get_status():
    # Simulating live data for the dashboard (since MQTT hardware isn't connected yet)
    flow = random.uniform(18.0, 25.0)
    c3_val = c3_calc.calculate_c3("PUMP_ON", flow)
    status = c3_calc.get_status(c3_val)

    return jsonify({
        "node": "water_1",
        "flow": round(flow, 2),
        "c3_index": c3_val,
        "status": status,
        "water_saved": 250000,
        "power_saved": 1500
    })

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)