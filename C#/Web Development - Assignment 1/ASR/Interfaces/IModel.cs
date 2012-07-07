using System;
using System.Collections.Generic;
using ASR.Model;

namespace ASR.Interfaces
{
    /// <summary>
    /// Inteface for the Model which extends IObservableModel inteface
    /// </summary>
    public interface IModel : IObservableModel
    {
        void LoadUsers(string Filename);
        void ListRooms();
        void ListSlots(DateTime? forDate);
        void ListTeachers();
        void ListStudents();
        void MakeBooking(Teacher Teacher, Student Student, Room R, Slot Slot);

        //Properties
        List<Room> Rooms { get; }
        Dictionary<string, Person> Teachers { get; }
        Dictionary<string, Person> Students { get; }
    }

    //Events that can be observed (Notably by the View)
    public interface IObservableModel
    {
        event ChangedEvent onChanged;
        event RoomsEvent OnRooms;
        event SlotsEvent OnSlots;
        event PersonsEvent OnPeople;
    }
}
