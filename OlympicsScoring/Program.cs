using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OlympicsScoring {

    /// <summary>
    /// A class that enables to calculate and display the Winners(competitiors - 
    /// who have acheived the highest scores and the judges who have awarded 
    /// total highest score to the competitors) from the given results data
    /// of Olympics events.
    /// Name - Harmanjeet Singh Student No: N9920811
    /// </summary>
    class Program {
        const int FIRST_INDEX = 0; 
        const int MIN_SCORE = 0;
        const int NO_WINNER = 0;
        const int ONE_WINNER = 1;
        const int SCORE_OF_ZERO = 0;


        public static void Main(string[] args) {

            int[,] results ={
                              { 4, 7, 9, 3, 8, 6},
                              { 4, 8, 6, 4, 8, 5}
                                
                            };
            DisplayWelcomeMessage();
            DisplayResultsMessage();
            int[] competitorsFinalScore = CalculateCompetitorsTotalScore(results);
            int[] judgesFinalScore = CalculateJudgesScore(results);
            DisplayCompetitorScores(competitorsFinalScore, results);
            DisplayWinnerCompetitor(competitorsFinalScore);
            DisplayWinnerJudge(judgesFinalScore);
            DisplayEndProgramMessage();
            EndProgram();

        } // end Main

        /// <summary>
        /// Display Welcome Message
        /// </summary>
        public static void DisplayWelcomeMessage() {
            Console.WriteLine("Welcome to the BrisVegas Winter Olympics 2017");
        } // end DisplayWelcomeMessage

        /// <summary>
        ///  Display Results Message
        /// </summary>
        public static void DisplayResultsMessage() {
            string message = "\nHere are the latest results:\n*********************************************\n";
            Console.WriteLine(message);

        } // end DisplayResultsMessage

        /// <summary>
        /// Calculate each competitor's score by adding all
        /// the scores except the lowest and the highest score
        /// </summary>
        /// <param name="results">Scores of Competitors and Judges</param>
        /// <returns>Returns Calculated total score of each competitor</returns>
        public static int[] CalculateCompetitorsTotalScore(int[,] results) {
            int numberOfCompetitors = results.GetLength(0);
            int numberOfScoresOfEachCompetitor = results.GetLength(1);
            int[] competitor = new int[numberOfScoresOfEachCompetitor];
            int[] competitorScores = new int[numberOfCompetitors];
            for (int competitorIndex = FIRST_INDEX; competitorIndex < numberOfCompetitors; competitorIndex++) {

                for (int indexEachScore = FIRST_INDEX; indexEachScore < numberOfScoresOfEachCompetitor; indexEachScore++) {
                    competitor[indexEachScore] = results[competitorIndex, indexEachScore];
                } // end for

                int maxScore = competitor[FIRST_INDEX];
                int minScore = competitor[FIRST_INDEX];
                int numberOfScoresOfCompetitor = competitor.Length;
                int eachCompetitorScore = MIN_SCORE;

                for (int indexOfEachScoreOfCompetitor = FIRST_INDEX; indexOfEachScoreOfCompetitor < numberOfScoresOfCompetitor; indexOfEachScoreOfCompetitor++) {
                    if (competitor[indexOfEachScoreOfCompetitor] > maxScore) {
                        maxScore = competitor[indexOfEachScoreOfCompetitor];
                    } else if (competitor[indexOfEachScoreOfCompetitor] < minScore) {
                        minScore = competitor[indexOfEachScoreOfCompetitor];
                    } //end if else if
                    eachCompetitorScore = eachCompetitorScore + competitor[indexOfEachScoreOfCompetitor];
                } // end for
                eachCompetitorScore = eachCompetitorScore - maxScore - minScore;

                competitorScores[competitorIndex] = eachCompetitorScore;


            } // end for
            return competitorScores;
        } // end CalculateCompetitorsScore

        /// <summary>
        /// Calculate total scores given by judges to each 
        /// competitor by adding up the scores 
        /// </summary>
        /// <param name="results">Scores of Competitors and Judges</param>
        /// <returns>Returns Calculated total score given by each judge to the each competitor</returns>
        public static int[] CalculateJudgesScore(int[,] results) {
            int numberOfJudges = results.GetLength(1);
            int numberOfScoresByEachJudge = results.GetLength(0);
            int[] judges = new int[numberOfScoresByEachJudge];
            int[] judgesScores = new int[numberOfJudges];
            for (int judgeIndex = FIRST_INDEX; judgeIndex < numberOfJudges; judgeIndex++) {
                int eachScoreByJudge = MIN_SCORE;
                for (int indexEachScore = FIRST_INDEX; indexEachScore < numberOfScoresByEachJudge; indexEachScore++) {
                    judges[indexEachScore] = results[indexEachScore, judgeIndex];
                    eachScoreByJudge = eachScoreByJudge + judges[indexEachScore];
                } // end for
                judgesScores[judgeIndex] = eachScoreByJudge;

            } // end for
            return judgesScores;
        } // end CalculateJudgesScore

        /// <summary>
        /// Display all the scores acheived by each Competitor and 
        /// display total score of each competitor
        /// </summary>
        /// <param name="competitorsFinalScore">Each Competitor's total score</param>
        /// <param name="results">All the scores of competitor awarded by all the judges</param>
        public static void DisplayCompetitorScores(int[] competitorsFinalScore, int[,] results) {
            int totalCompetitors = results.GetLength(0);
            int NumberOfCompetitorScores = results.GetLength(1);
            for (int competitorNumber = FIRST_INDEX; competitorNumber < totalCompetitors; competitorNumber++) {
                Console.Write("Competitor " + (competitorNumber + 1) + ":\tyour scores were:");

                for (int indexOfEachScore = FIRST_INDEX; indexOfEachScore < NumberOfCompetitorScores; indexOfEachScore++) {
                    Console.Write(" " + results[competitorNumber, indexOfEachScore]);
                } // end for
                Console.Write("\n\t\twith a total of " + competitorsFinalScore[competitorNumber]);
                Console.Write("\n\n");
            } // end for


        } // end DisplayCompetitorScores

        /// <summary>
        /// Display the winner competitior with the highest score
        /// or winner competitors with same highest score
        /// </summary>
        /// <param name="competitorsFinalScore">Each Competitor's total score</param>
        public static void DisplayWinnerCompetitor(int[] competitorsFinalScore) {
            int maxScore = SCORE_OF_ZERO;
            int totalScoresOfEachCompetitors = competitorsFinalScore.Length;
            for (int indexOfCompetitorsScore = FIRST_INDEX; indexOfCompetitorsScore < totalScoresOfEachCompetitors; indexOfCompetitorsScore++) {
                if (maxScore < competitorsFinalScore[indexOfCompetitorsScore]) {
                    maxScore = competitorsFinalScore[indexOfCompetitorsScore];
                } // end if 
            } // end for
            int countWinners = NO_WINNER;
            for (int indexOfCompetitorsScore = FIRST_INDEX; indexOfCompetitorsScore < totalScoresOfEachCompetitors; indexOfCompetitorsScore++) {
                if (maxScore == competitorsFinalScore[indexOfCompetitorsScore]) {
                    countWinners++;

                } // end if
            } // end for
            if (countWinners == ONE_WINNER) {
                Console.WriteLine("And the winner is ...");

            } else {
                Console.WriteLine("And the winners are ...");

            } // end if else



            for (int indexOfCompetitorsScore = FIRST_INDEX; indexOfCompetitorsScore < totalScoresOfEachCompetitors; indexOfCompetitorsScore++) {
                if (maxScore == competitorsFinalScore[indexOfCompetitorsScore]) {
                    Console.WriteLine("\n\t\tCompetitor " + (indexOfCompetitorsScore + 1) + " with a score of " + competitorsFinalScore[indexOfCompetitorsScore]);

                } // end if
            } // end for
        } // end DisplayWinnerCompetitor

        /// <summary>
        /// Display the judge or judges who have awarded 
        /// highest scores to the competitors
        /// </summary>
        /// <param name="judgesFinalScore">Total scores awarded by each judge</param>
        public static void DisplayWinnerJudge(int[] judgesFinalScore) {
            int maxScore = SCORE_OF_ZERO;
            int totalJudges = judgesFinalScore.Length;
            for (int indexOfEachScoreOfJudge = FIRST_INDEX; indexOfEachScoreOfJudge < totalJudges; indexOfEachScoreOfJudge++) {
                if (maxScore < judgesFinalScore[indexOfEachScoreOfJudge]) {
                    maxScore = judgesFinalScore[indexOfEachScoreOfJudge];
                } // end if
            } // end for
            int countWinners = NO_WINNER;
            for (int indexOfEachScoreOfJudge = FIRST_INDEX; indexOfEachScoreOfJudge < totalJudges; indexOfEachScoreOfJudge++) {
                if (maxScore == judgesFinalScore[indexOfEachScoreOfJudge]) {
                    countWinners++;
                } // end if
            } // end for
            if (countWinners == ONE_WINNER) {
                Console.WriteLine("\n\nAnd the judge with the highest score is ...\n");                          

            } else {
                Console.WriteLine("\n\nAnd the judges with the highest score are ...\n");

            } // end if else


            for (int indexOfEachScoreOfJudge = FIRST_INDEX; indexOfEachScoreOfJudge < totalJudges; indexOfEachScoreOfJudge++) {
                if (judgesFinalScore[indexOfEachScoreOfJudge] == maxScore) {
                    Console.WriteLine("\t\tJudge " + (indexOfEachScoreOfJudge + 1) + " with a score total of " + judgesFinalScore[indexOfEachScoreOfJudge]);

                } // end if

            } // end for

        } // end DisplayWinnerJudge

        /// <summary>
        /// Display End program message
        /// </summary>
        public static void DisplayEndProgramMessage() {
            string message = "\n\n*********************************************\nThat's all for now";
            Console.WriteLine(message);
        } // end DisplayEndProgramMessage

        /// <summary>
        /// End the program by accepting any key press
        /// </summary>
        public static void EndProgram() {
            Console.WriteLine("Press any key to exit...");
            Console.ReadKey();
        } // end EndProgram


    } // end class

} // end namespace



