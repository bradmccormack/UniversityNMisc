using ASR.Controller;
using ASR.Interfaces;

namespace ASR.Driver
{
    class Program
    {
        static void Main(string[] args)
        {
            IModel model = new ASR.Model.Model();
            //Start up the controller and pass in the view (with model reference) and model
            MainController controller = new MainController(new ASR.View.MainConsoleView(model), model);
            if (args.Length > 0)
            {
                controller.Start(args[0]);
            }
            else
            {
                controller.Start("Support/users.txt");
            }

            //When the controller goes out of scope the app will finish and everything will be garbage collected
        }
    }
}
