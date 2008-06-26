hold on

xlabel('Cantidad de nodos en cada particion')
ylabel('Cantidad de cruces')

plot(x, crucesConstructiva - crucesExacto,'b')
plot(x, crucesLocal - crucesExacto,'r')
plot(x, crucesGrasp - crucesExacto,'g')

legend('Constructiva - Exacto', 'Local - Exacto', 'Grasp - Exacto', 'Location', 'NorthWest')