using System;

///Various Custom exceptions used throughout the ASR system
namespace ASR.Exceptions
{
    public class SlotMaximumException : Exception
    {
        public SlotMaximumException(string Message) : base(Message) { }
    }

    public class SlotPermissionException : Exception
    {
        public SlotPermissionException(string Message) : base(Message) { }
    }

    public class ASRFileFormatException : Exception
    {
        public ASRFileFormatException(string Message) : base(Message) { }
    }
}
