using System;
using System.Collections.Generic;
using System.Linq;

namespace ASR.Utilitiy
{
    //Generic helpers that are used by the ASR system
    public static class Helper
    {
        // This method makes a divider by returning a string of a particular character repeated Amount times
        public static string Divider(char Div, int Amount)
        {
            return new string(Div, Amount);
        }

        //Takes An enum Type and returns a list of that type
        public static List<T> ToList<T>() where T : struct
        {
            return Enum.GetValues(typeof(T)).Cast<T>().ToList();
        }

    }
}
