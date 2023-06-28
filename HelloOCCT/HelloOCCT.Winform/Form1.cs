using System.Windows.Forms;

namespace HelloOCCT.Winform
{
    public partial class Form1 : Form
    {
        Viewport viewport;

        public Form1()
        {
            InitializeComponent();

            viewport = new Viewport();
            viewport.Initialize(this.Handle);
            viewport.SetBackgroudColor(System.Drawing.Color.Red);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            viewport.Update();
        }
    }
}
