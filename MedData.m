
% prompt user to enter in the file name
prompt = 'Enter the name of the file ';
%user enters in file name in _drugID_patId_info.txt format and the name is
%stored in fileName variable
fileName = input(prompt, 's');
%read in the drugID & patID from the user for the data, we're doing this so
%that we may specify the drug & patient in our plot
DrugID = input('Enter in the drug ID: ');
patID = input('Enter in the patient ID: ');
%open the file corresponding to the entered value for filename
fileID = fopen(fileName);
% scan the first line until we reach the second, and discard the data
% stored there
fscanf(fileID,'%*[^\n]');
% scan the second line of the file and store the float values read into
% array C
C = fscanf(fileID, '%f'); 
% then close the file
fclose(fileID);
% create vector t that has values from 1 to 24
t = 1:24;
%Define the absorption rate formula as it varies with t
Absorption = C(5)*C(4)*C(1)*exp(-C(5)*t);
%Define the concentration rate formula as it varies with t
Concentration = 533.3*(exp(-.4*t)-exp(-.5*t));
%use the sprintf function to place the drugId & patientID into a string, and store it within string str. this will be our title 
str = sprintf('The rate of Absorption/Concentration of drug %04d on patient %02d over time', DrugID, patID);
%create a figure and plot the absorption rate vs t with red asterisks
figure
plot(t,Absorption,'r*')
hold on;
%plot the concentration rate vs t with a blue line
plot(t,Concentration,'b-');
%label the x axis for t (hours)
xlabel('t (hours)')
%label the y axis rate, the units are not known
ylabel('rate')
%turn the grid on, and use the earlier string str as your plot title
grid on
title(str);
%finally create a legend so that we may differentiate which line is for
%absorption rate and which is for concentration rate
legend('absorption rate', 'concentration rate')


%create vector for time variable (x axis)
