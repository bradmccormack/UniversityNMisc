using System;
using System.Collections.Generic;
using System.IO;
using ASR.Model;
using System.Text.RegularExpressions;

//http://myregextester.com/index.php

namespace ASR.Utilitiy
{
    /// <summary>
    /// Helper class to handle ASR Input files
    /// </summary>
    public static class ASRTextFileLoader
    {
        /// <summary>
        /// Loads in an ASR Input file and populates the users of the system
        /// </summary>
        /// <param name="Filename"></param>
        /// <returns></returns>
        public static Dictionary<string, Person> LoadPersonDetails(string Filename)
        {
            if (!File.Exists(Filename))
            {
                throw new FileNotFoundException(String.Format("{0} Not found. Cannot load that user's file", Filename));
            }
            StreamReader file = null;
            Dictionary<string, Person> people = new Dictionary<string, Person>();
            try
            {
                file = new StreamReader(Filename);
                //Setup the regular expressions engine
                Regex re = new Regex(@"(.*), ( (e\d{7}),(e\d{7}@ems.rmit.edu.au) | (s\d{7}),(s\d{7}@student.rmit.edu.au))",
                    RegexOptions.IgnoreCase |
                    RegexOptions.IgnorePatternWhitespace);

                string line;
                int i = 1;
                while ((line = file.ReadLine()) != null)
                {
                    //Check for match. A Match is mandatory. IF not matched then the file is malformed
                    Match m = re.Match(line);
                    if (!m.Success)
                    {
                        throw new ASR.Exceptions.ASRFileFormatException(
                            String.Format("File is malformed. Error processing {0}, error occured on line {1} with contents of {2}",
                            Filename,
                            i,
                            line
                            ));
                    }
                    //Pull out the components of the line
                    string name = m.Groups[1].Value;
                    //Teacher is evaluated first. Test if that matched and if so assign id and email for teacher else assign for student
                    string id = !String.IsNullOrEmpty(m.Groups[3].Value) ? m.Groups[3].Value : m.Groups[5].Value;
                    string email = !String.IsNullOrEmpty(m.Groups[4].Value) ? m.Groups[4].Value : m.Groups[6].Value;

                    //Make sure the ID for staff / student is unique
                    if (people.ContainsKey(id))
                    {
                        throw new ASR.Exceptions.ASRFileFormatException(
                            String.Format("File is malformed. Error processing {0}, error occured on line {1} found an ID that already exists {2}",
                            Filename,
                            i,
                            id));
                    }
                    //Create a new Teacher or Student Person and add to the collection
                    if (id.StartsWith("e"))
                    {
                        people.Add(id, new Teacher(name, id, email));
                    }
                    else
                    {
                        people.Add(id, new Student(name, id, email));
                    }
                    i++;
                }
            }
            finally
            {
                file.Close();
            }
            return people;
        }
    }
}
