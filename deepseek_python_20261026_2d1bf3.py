class C3IndexCalculator:
    def __init__(self, max_flow=30.0):
        self.max_flow = max_flow 
        self.thresholds = {'normal': 0.95, 'warning': 0.70, 'critical': 0.30}

    def calculate_c3(self, network_command, physical_flow):
        N = 1.0 if network_command == "PUMP_ON" else 0.0
        P = min(max(physical_flow, 0) / self.max_flow, 1.0)
        c3 = 1.0 - abs(N - P)
        return round(max(0.0, min(1.0, c3)), 4)

    def get_status(self, c3_value):
        if c3_value >= self.thresholds['normal']: return "NORMAL"
        elif c3_value >= self.thresholds['warning']: return "WARNING"
        elif c3_value >= self.thresholds['critical']: return "CRITICAL"
        else: return "ATTACK"