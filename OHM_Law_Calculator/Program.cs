using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OHM_Law_Calculator {

    /// <summary>
    /// Ohm’s Law:  Voltage = Current * Resistance
    /// Given any two of the three quantities in Ohm’s Law, calculate the
    /// program calculate the third.
    /// Name: Harmanjeet Singh, Student Number: N9920811
    /// Date: July, 2017    
    /// </summary>

    class Program {

        const int VOLTAGE = 1;
        const int CURRENT = 2;
        const int RESISTANCE = 3;
        const int EXIT = 0;
        const double MIN_VOLTAGE = 0.0;
        const double MIN_CURRENT = 0.01;
        const int MIN_RESISTANCE = 10;

        static void Main(string[] args) {
            int UserChoice;

            ShowWelcomeMessage();

            do {

                DisplayMenu();
                UserChoice = GetUserInput();

                if (UserChoice == VOLTAGE) {
                    CalculateVoltage();
                } else if (UserChoice == CURRENT) {
                    CalculateCurrent();
                } else if (UserChoice == RESISTANCE) {
                    CalculateResistance();
                } else {
                    ThanksMessage();
                    ExitProgram();
                } // End of if - else-if - else 

            } while (UserChoice != EXIT); //End of do - while

        }

        public static void ShowWelcomeMessage() {
            Console.WriteLine("************************************** ");
            Console.WriteLine("Welcome to the Ohm's Law Calculator ");
            Console.WriteLine("************************************** ");

        } //End of ShowWelcomeMessage

        public static void DisplayMenu() {

            Console.WriteLine("\nMain Menu:\n ====================");
            Console.WriteLine("1: voltage\n2: current \n3: resistance \n0: exit");

        } //End of DisplayMenu

        public static int GetUserInput() {
            string UserInput;
            int ValidUserChoice;
            bool IsChoiceValid = false;
            Console.Write("\nChoose an Option: ");
            UserInput = Console.ReadLine();
            IsChoiceValid = int.TryParse(UserInput, out ValidUserChoice);

            while ((!IsChoiceValid) || (ValidUserChoice < 0) || (ValidUserChoice >= 4)) {

                Console.Write("\n\aYou have entered invalid character. Please Enter a valid option: ");
                UserInput = Console.ReadLine();
                IsChoiceValid = int.TryParse(UserInput, out ValidUserChoice);


            } // End of while

            return ValidUserChoice;
        } //End of GetUserInput


        public static void CalculateVoltage() {
            Console.WriteLine("\nPerforming a calculation for voltage...");
            double UserCurrentValue = GetCurrentValue();
            double UserResistanceValue = GetResistanceValue();
            double ResultedVoltageValue = UserCurrentValue * UserResistanceValue;
            DisplayCalculatedVoltage(UserCurrentValue, UserResistanceValue, ResultedVoltageValue);


        } // End of CalculateVoltage

        public static void CalculateCurrent() {
            Console.WriteLine("\nPerforming a calculation for current...");
            double UserVoltageValue = GetVoltageValue();
            double UserResistanceValue = GetResistanceValue();
            double ResultedCurrentValue = UserVoltageValue / UserResistanceValue;
            DisplayCalculatedCurrent(UserVoltageValue, UserResistanceValue, ResultedCurrentValue);

        } //End of CalculateCurrent

        public static void CalculateResistance() {
            Console.WriteLine("\nPerforming a calculation for Resistance...");
            double UserCurrentValue = GetCurrentValue();
            double UserVoltageValue = GetVoltageValue();
            double ResultedResistanceValue = UserVoltageValue / UserCurrentValue;
            DisplayCalculatedResistance(UserCurrentValue, UserVoltageValue, ResultedResistanceValue);


        } //End of CalculateResistance

        public static double GetVoltageValue() {
            string UserEntry = "";
            double UserVoltageValue;
            bool ValueIsValid;
            Console.Write("\nEnter a value for voltage(at least 0.0 volt):");
            UserEntry = Console.ReadLine();
            ValueIsValid = double.TryParse(UserEntry, out UserVoltageValue);
            while ((!ValueIsValid) || (UserVoltageValue < MIN_VOLTAGE) || (UserVoltageValue > double.MaxValue)) {

                Console.Write("\n\aYou have not entered a valid value for voltage! \nVoltage value must be >= 0.0 volt. \nPlease enter Voltage value again: ");
                UserEntry = Console.ReadLine();
                ValueIsValid = double.TryParse(UserEntry, out UserVoltageValue);
            } //End of while

            return UserVoltageValue;

        } //End of GetVoltageValue

        public static double GetCurrentValue() {
            string UserEntry = "";
            double UserCurrentValue;
            bool ValueIsValid;
            Console.Write("\nEnter a value for current(at least 0.01 amp):");
            UserEntry = Console.ReadLine();
            ValueIsValid = double.TryParse(UserEntry, out UserCurrentValue);
            while ((!ValueIsValid) || (UserCurrentValue < MIN_CURRENT) || (UserCurrentValue > double.MaxValue)) {
                Console.Write("\n\aYou have not entered a valid value for current! \nCurrent's value must be >= 0.01 amp. \nPlease enter Current value again: ");
                UserEntry = Console.ReadLine();
                ValueIsValid = double.TryParse(UserEntry, out UserCurrentValue);
            } //End of while

            return UserCurrentValue;

        } //End of GetCurrentValue


        public static double GetResistanceValue() {
            string UserEntry = "";
            double UserResistanceValue;
            bool ValueIsValid;
            Console.Write("\nEnter a value for resistance(at least 10 ohm):");
            UserEntry = Console.ReadLine();
            ValueIsValid = double.TryParse(UserEntry, out UserResistanceValue);
            while ((!ValueIsValid) || (UserResistanceValue < MIN_RESISTANCE) || (UserResistanceValue > double.MaxValue)) {

                Console.Write("\n\aYou have not entered a valid value for resistance! \nResistance value must be >= 10 ohm. \nPlease enter Resistance Value again: ");
                UserEntry = Console.ReadLine();
                ValueIsValid = double.TryParse(UserEntry, out UserResistanceValue);
            } // End of while

            return UserResistanceValue;

        } //End of GetResistanceValue


        public static void DisplayCalculatedVoltage(double current, double resistance, double voltage) {
            Console.WriteLine("\nFor Current of {0} amp and resistance of {1} ohm, \nthe resulted voltage is {2:f2} volt", current, resistance, voltage);
            Console.Write("\nPress ENTER to continue...");
            Console.ReadLine();
        } //End of DisplayCalculatedVoltage

        public static void DisplayCalculatedCurrent(double voltage, double resistance, double current) {
            Console.WriteLine("\nFor Voltage of {0} volt and resistance of {1} ohm, \nthe resulted current is {2:f2} amp", voltage, resistance, current);
            Console.Write("\nPress ENTER to continue...");
            Console.ReadLine();
        } //End of DisplayCalculatedCurrent

        public static void DisplayCalculatedResistance(double current, double voltage, double resistance) {
            Console.WriteLine("\nFor Current of {0} amp and voltage of {1} volt, \nthe resulted resistance is {2:f2} volt", current, voltage, resistance);
            Console.Write("\nPress ENTER to continue...");
            Console.ReadLine();
        } //End of DisplayCalculatedResistance

        public static void ThanksMessage()
        {
            Console.WriteLine("\nThanks for using the Ohm's Law Calculator ");

        }


        public static void ExitProgram() {
            
            Console.Write("\nPress Enter to continue . . .  ");

            Console.ReadLine();

        } //End of ExitProgram
    }
}
