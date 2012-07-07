using System;
using System.Collections.Generic;

namespace ASR.Model
{
    /// <summary>
    /// Abstract Person class which provides foundations for further specialised Person subclasses.
    /// </summary>
    public abstract class Person
    {
        protected string _name;
        protected string _id;
        protected string _email;

        public Person(String Name, String ID, String Email)
        {
            _name = Name;
            _id = ID;
            _email = Email;
            Bookings = new List<Slot>();
        }

        #region Properties
        public string Name
        {
            get
            {
                return _name;
            }
            set
            {
                if (!String.IsNullOrEmpty(value))
                {
                    _name = value;
                }
            }
        }

        public string Id
        {
            get
            {
                return _id;
            }
            set
            {
                if (!String.IsNullOrEmpty(value))
                {
                    _id = value;
                }
            }
        }

        public string Email
        {
            get
            {
                return _email;
            }
            set
            {
                if (!String.IsNullOrEmpty(value))
                {
                    _email = value;
                }
            }
        }

        /// <summary>
        /// Maintains a List of Bookings for the Staff Member. Use implicit properties
        /// </summary>
        public List<Slot> Bookings
        {
            get;
            private set;
        }

        #endregion

    }
}
