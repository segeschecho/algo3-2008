hold on

xlabel('Cantidad de nodos en cada particion')
ylabel('Tiempo (segundos)')

plot(x, tiemposExacto,'black')
plot(x, tiemposConstructiva,'b')
plot(x, tiemposLocal,'r')
plot(x, tiemposGrasp,'g')

legend('Exacto', 'Constructiva', 'Local', 'Grasp', 'Location', 'NorthWest')