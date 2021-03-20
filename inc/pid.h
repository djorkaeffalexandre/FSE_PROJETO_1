#ifndef PID_H_
#define PID_H_

void pid_configura_constantes(double Kp_, double Ki_, double Kd_);
void pid_atualiza_referencia(float referencia_);
double pid_controle(double saida_medida);
void pid_limpa_referencia_usuario();
void pid_referencia_usuario(float referencia_);
float pid_le_referencia();

#endif /* PID_H_ */
