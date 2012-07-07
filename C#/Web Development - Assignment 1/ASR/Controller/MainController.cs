using System;
using ASR.Interfaces;
using ASR.Model;

namespace ASR.Controller
{
    public class MainController
    {
        private bool _quit;

        private IMainView _view;
        private IModel _model;

        //Inversion of control. Pass in the dependencies
        public MainController(IMainView View, IModel Model)
        {
            _view = View;
            _model = Model;
        }

        /// <summary>
        /// The Staff Sub-menu
        /// </summary>
        private void ShowStaff()
        {
            DataTypes.MenuStaffOptions? choice = null;
            do
            {
                choice = _view.GetStaffMenuOption("Staff Menu");
                switch (choice)
                {
                    case (DataTypes.MenuStaffOptions.List_Staff):
                        {
                            _view.Write("Existing Teachers:");
                            _model.ListTeachers();
                            break;
                        }
                    case (DataTypes.MenuStaffOptions.Room_Availability):
                        {
                            _view.RoomAvailability();
                            break;
                        }
                    case (DataTypes.MenuStaffOptions.Create_Slot):
                        {
                            try
                            {
                                _view.CreateSlot();
                                _view.Write("Slot created successfully");
                            }
                            catch (ASR.Exceptions.SlotMaximumException ex)
                            {
                                _view.Write(ex.Message);
                            }
                            catch (ASR.Exceptions.SlotPermissionException ex)
                            {
                                _view.Write(ex.Message);

                            }
                            catch (ArgumentException ex)
                            {
                                _view.Write(ex.Message);
                            }
                            break;
                        }
                    case (DataTypes.MenuStaffOptions.Remove_Slot):
                        {
                            try
                            {
                                _view.DeleteSlot();
                            }
                            catch (ASR.Exceptions.SlotPermissionException ex)
                            {
                                _view.Write(ex.Message);
                            }
                            break;

                        }
                    case (DataTypes.MenuStaffOptions.Exit):
                        {
                            _view.Write("Exiting staff menu");
                            break;
                        }
                }
            } while (choice != DataTypes.MenuStaffOptions.Exit);
        }

        /// <summary>
        /// The Student Sub-menu
        /// </summary>
        private void ShowStudent()
        {
            DataTypes.MenuStudentOptions? choice = null;
            do
            {
                choice = _view.GetStudentMenuOption("Student Menu");
                switch (choice)
                {
                    case (DataTypes.MenuStudentOptions.List_Students):
                        {
                            _view.Write("Existing students:");
                            _model.ListStudents();
                            break;
                        }
                    case (DataTypes.MenuStudentOptions.Staff_Availability):
                        {
                            _view.Write("Staff availablitity");
                            _view.ListAvailability();
                            break;

                        }
                    case (DataTypes.MenuStudentOptions.Make_Booking):
                        {
                            try
                            {
                                _view.MakeBooking();
                                _view.Write("Booking complete");
                            }
                            // I could use a generic catch block but I'll be explicit should I decide to change the way I handle specific exceptions later.
                            catch (ASR.Exceptions.SlotMaximumException ex)
                            {
                                _view.Write(ex.Message);
                            }
                            catch (ASR.Exceptions.SlotPermissionException ex)
                            {
                                _view.Write(ex.Message);
                            }
                            catch (ArgumentException ex)
                            {
                                _view.Write(ex.Message);
                            }
                            break;
                        }
                    case (DataTypes.MenuStudentOptions.Cancel_Booking):
                        {
                            try
                            {
                                _view.CancelBooking();
                            }
                            catch (Exception ex)
                            {
                                _view.Write(ex.Message);
                            }
                            break;
                        }

                    case (DataTypes.MenuStudentOptions.Exit):
                        {
                            _view.Write("Exiting student menu");
                            break;
                        }
                }
            } while (choice != DataTypes.MenuStudentOptions.Exit);
        }

        private void ShowMain()
        {
            while (!_quit)
            {
                //Display menu, Get a selection and react accordingly.
                DataTypes.MenuMainOptions choice = _view.GetMainMenuOption("Main Menu");
                switch (choice)
                {
                    case (DataTypes.MenuMainOptions.List_Rooms):
                        {
                            //Request the model retrieve the rooms and notify the view when ready
                            _model.ListRooms();
                            break;
                        }
                    case (DataTypes.MenuMainOptions.List_Slots):
                        {
                            //Request the model retrieve the slots and notify the view when ready
                            _model.ListSlots(null);
                            break;
                        }

                    case (DataTypes.MenuMainOptions.Staff_Menu):
                        {
                            ShowStaff();
                            break;
                        }
                    case (DataTypes.MenuMainOptions.Student_Menu):
                        {
                            ShowStudent();
                            break;
                        }
                    case (DataTypes.MenuMainOptions.Exit):
                        {
                            _view.ShowExit();
                            _quit = true;
                            break;
                        }
                }
            }
        }

        public void Start(string Filename)
        {
            //Read in the users file and display a welcome message whilst handling errors that may come up
            try
            {
                _model.LoadUsers(Filename);
                _view.ShowWelcome();
            }
            //The file is malformed
            catch (ASR.Exceptions.ASRFileFormatException ex)
            {
                _view.Write(ex.Message);
                _view.Write("Press any key...");
                Console.ReadKey();
                return;
            }
            //Some other Exception occured to do with parsing the specified file
            catch (Exception ex)
            {
                _view.Write(ex.Message);
                _view.Write("Press any key...");
                Console.ReadKey();
                return;
            }
            ShowMain();
        }

    }
}
