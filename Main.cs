namespace ProyectoSOver1
{
    using System;
    using System.Net;
    using System.Net.Sockets;
    using System.IO;
    using System.Text;
    public partial class Form1 : Form
    {
        Socket socket;
        public Form1()
        {
            InitializeComponent();

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e) //iniciar sesion
        {

            string us;
            string con;
            string uscon;
            us = Convert.ToString(textBox1.Text);
            con = Convert.ToString(textBox2.Text);
            uscon = us + "," + con;
            byte[] mensaje = Encoding.ASCII.GetBytes(uscon);
            byte[] respuesta;
            socket.Send(mensaje);
            socket.Receive(respuesta);
            socket.Close();
            socket.Close();
        }

        private void button2_Click(object sender, EventArgs e) //Conectarse al server
        {
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPEndPoint remoteEP = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 9050);
            try
            {
                socket.Connect(remoteEP);
                label13.Text = "Se ha conectado correctamente al servidor";
            }
            catch (SocketException)
            {
                label11.Text = "Ha sido imposible conectarse con el servidor";
                return;
            }
        }

        private void button7_Click(object sender, EventArgs e) //desconectarse del servidor
        {
            socket.Close();
        }

        private void button6_Click(object sender, EventArgs e) //crear usuario
        {
            string us;
            string con;
            string uscon;
            us = Convert.ToString(textBox1.Text);
            con = Convert.ToString(textBox2.Text);
            uscon = us + "," + con;
            byte[] mensaje = Encoding.ASCII.GetBytes(uscon);
            socket.Send(mensaje);
            socket.Receive(byte[] respuesta);

        }

        private void button3_Click(object sender, EventArgs e) //consulta 1
        {

        }

        private void button4_Click(object sender, EventArgs e) //Consulta 2
        {

        }

        private void button5_Click(object sender, EventArgs e) //Consulta 3
        {

        }
    }
}