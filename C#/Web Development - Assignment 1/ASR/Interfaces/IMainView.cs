using System;
using ASR.Model;
namespace ASR.Interfaces
{
    //Can be console, asp.net frontend etc
    public interface IMainView
    {
        // Menu related methods
        DataTypes.MenuMainOptions GetMainMenuOption(string Heading);
        DataTypes.MenuStaffOptions GetStaffMenuOption(string Heading);
        DataTypes.MenuStudentOptions GetStudentMenuOption(string Heading);

        //Input related methods
        void CreateSlot();
        void DeleteSlot();
        void ListAvailability();
        void MakeBooking();
        void CancelBooking();
        void RoomAvailability();

        //Display related methods
        void ShowWelcome();
        void ShowExit();
        void Write(String s);


    }
}
