/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package juego_gato;
import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import java.awt.Font;
import java.awt.Color;
import javax.swing.JButton;
import javax.swing.SwingConstants;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.Random;



/**
 *
 * @author cheche
 */


public class Juego_gato extends JFrame implements ActionListener {
	private static final long serialVersionUID = 1L;

	public class JLabelBox extends JLabel {

		private static final long serialVersionUID = 1L;
		public int Field = 0;
	}

	private int winX = 0;
	private int winO = 0;
	private int winE = 0;
        private int [] arre = new int[9];

	private JPanel ventana;
	private JButton newTablero, newJuego;
	private JLabelBox C1, C2, C3, C4, C5, C6, C7, C8, C9;
	private JLabel contaX, contaO, contaE;
	private JLabel texX;
	private JLabel texO;
	private JLabel texE;
	private JButton CvC;
        private algoritmo_Gato algo;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Juego_gato frame = new Juego_gato();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public Juego_gato() {
                for(int i=0;i<9;i++){
                    arre[i]=3;
                }
                algo = new algoritmo_Gato();
		setResizable(true);
		setTitle("GATO");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 250, 500);
		ventana = new JPanel();
		ventana.setBorder(new EmptyBorder(7, 7, 7, 7));
		setContentPane(ventana);
	    ventana.setLayout(null);

		C1 = new JLabelBox();
		C1.Field = 0;
		C1.addMouseListener(new LabelAdapter(C1));
		C1.setFont(new Font("Tahoma", Font.BOLD, 40));
		C1.setForeground(Color.GREEN);
		C1.setBackground(new Color(0, 0, 0));
		C1.setHorizontalAlignment(SwingConstants.CENTER);
		C1.setBounds(10, 100, 64, 64);
		C1.setOpaque(true);
		ventana.add(C1);

		C2 = new JLabelBox();
		C2.Field = 1;
		C2.addMouseListener(new LabelAdapter(C2));
		C2.setOpaque(true);
		C2.setHorizontalAlignment(SwingConstants.CENTER);
		C2.setForeground(Color.GREEN);
		C2.setFont(new Font("Tahoma", Font.BOLD, 40));
		C2.setBackground(Color.BLACK);
		C2.setBounds(76, 100, 64, 64);
		ventana.add(C2);

		C3 = new JLabelBox();
		C3.Field = 2;
		C3.addMouseListener(new LabelAdapter(C3));
		C3.setOpaque(true);
		C3.setHorizontalAlignment(SwingConstants.CENTER);
		C3.setForeground(Color.GREEN);
		C3.setFont(new Font("Tahoma", Font.BOLD, 40));
		C3.setBackground(Color.BLACK);
		C3.setBounds(142, 100, 64, 64);
		ventana.add(C3);

		C4 = new JLabelBox();
		C4.Field = 3;
		C4.addMouseListener(new LabelAdapter(C4));
		C4.setOpaque(true);
		C4.setHorizontalAlignment(SwingConstants.CENTER);
		C4.setForeground(Color.GREEN);
		C4.setFont(new Font("Tahoma", Font.BOLD, 40));
		C4.setBackground(Color.BLACK);
		C4.setBounds(10, 166, 64, 64);
		ventana.add(C4);

		C5 = new JLabelBox();
		C5.Field = 4;
		C5.addMouseListener(new LabelAdapter(C5));
		C5.setOpaque(true);
		C5.setHorizontalAlignment(SwingConstants.CENTER);
		C5.setForeground(Color.GREEN);
		C5.setFont(new Font("Tahoma", Font.BOLD, 40));
		C5.setBackground(Color.BLACK);
		C5.setBounds(76, 166, 64, 64);
		ventana.add(C5);

		C6 = new JLabelBox();
		C6.Field = 5;
		C6.addMouseListener(new LabelAdapter(C6));
		C6.setOpaque(true);
		C6.setHorizontalAlignment(SwingConstants.CENTER);
		C6.setForeground(Color.GREEN);
		C6.setFont(new Font("Tahoma", Font.BOLD, 40));
		C6.setBackground(Color.BLACK);
		C6.setBounds(142, 166, 64, 64);
		ventana.add(C6);

		C7 = new JLabelBox();
		C7.Field = 6;
		C7.addMouseListener(new LabelAdapter(C7));
		C7.setOpaque(true);
		C7.setHorizontalAlignment(SwingConstants.CENTER);
		C7.setForeground(Color.GREEN);
		C7.setFont(new Font("Tahoma", Font.BOLD, 40));
		C7.setBackground(Color.BLACK);
		C7.setBounds(10, 232, 64, 64);
		ventana.add(C7);

		C8 = new JLabelBox();
		C8.Field = 7;
		C8.addMouseListener(new LabelAdapter(C8));
		C8.setOpaque(true);
		C8.setHorizontalAlignment(SwingConstants.CENTER);
		C8.setForeground(Color.GREEN);
		C8.setFont(new Font("Tahoma", Font.BOLD, 40));
		C8.setBackground(Color.BLACK);
		C8.setBounds(76, 232, 64, 64);
		ventana.add(C8);

		C9 = new JLabelBox();
		C9.Field = 8;
		C9.addMouseListener(new LabelAdapter(C9));
		C9.setOpaque(true);
		C9.setHorizontalAlignment(SwingConstants.CENTER);
		C9.setForeground(Color.GREEN);
		C9.setFont(new Font("Tahoma", Font.BOLD, 40));
		C9.setBackground(Color.BLACK);
		C9.setBounds(142, 232, 64, 64);
		ventana.add(C9);

		newTablero= new JButton("Borrar tablero");
		newTablero.addActionListener(this);
		newTablero.setBounds(10, 50, 197, 23);
		ventana.add(newTablero);
                
		contaX = new JLabel("-");
		contaX.setFont(new Font("Tahoma", Font.BOLD, 17));
		contaX.setBounds(10, 300, 169, 36);
		ventana.add(contaX);

		contaO = new JLabel("-");
		contaO.setFont(new Font("Tahoma", Font.BOLD, 17));
		contaO.setBounds(10, 330, 169, 36);
		ventana.add(contaO);

		contaE = new JLabel("-");
		contaE.setFont(new Font("Tahoma", Font.BOLD, 17));
		contaE.setBounds(10, 360, 169, 30);
		ventana.add(contaE);

		newJuego = new JButton("Borrar");
		newJuego.setBounds(10, 400, 76, 23);
		newJuego.addActionListener(this);
		ventana.add(newJuego);

		texX = new JLabel("gana x:");
		texX.setFont(new Font("Tahoma", Font.BOLD, 17));
		texX.setHorizontalAlignment(SwingConstants.RIGHT);
		texX.setBounds(20, 300, 76, 36);
		ventana.add(texX);

		texO = new JLabel("gana o:");
		texO.setFont(new Font("Tahoma", Font.BOLD, 17));
		texO.setHorizontalAlignment(SwingConstants.RIGHT);
		texO.setBounds(30, 330, 66, 36);
		ventana.add(texO);

		texE = new JLabel("empate:");
		texE.setFont(new Font("Tahoma", Font.BOLD, 17));
		texE.setHorizontalAlignment(SwingConstants.RIGHT);
		texE.setBounds(25, 360, 76, 30);
		ventana.add(texE);

		//CvC = new JButton("PC vs PC");
		//CvC.setBounds(10, 10, 169, 23);
		//CvC.addActionListener(this);
		//ventana.add(CvC);
	}

	public void actionPerformed(ActionEvent e) {

		if (e.getSource() == newTablero) {
                        NewGame();
		}

		if (e.getSource() == newJuego) {
			SetCounters(2);
		}

		if (e.getSource() == CvC) {
			CvC();
		}
	}

	public void SetCounters(int Num) {
		switch (Num) {
		case -1:
			winX++;
			break;
		case 1:
			winO++;
			break;
		case 0:
			winE++;
			break;
		case 2:
			winX = 0;
			winO = 0;
			winE = 0;
			break;
		}
		contaX.setText(winX + "");
		contaO.setText(winO + "");
		contaE.setText(winE + "");
	}

	class LabelAdapter extends MouseAdapter {
		JLabelBox sender;

		public LabelAdapter(JLabelBox sender) {
			this.sender = sender;
		}

		public void mouseReleased(MouseEvent me) {
			int GO = algo.Gameover(arre);
			if ((arre[sender.Field] == 3) && (GO == 0)) {
				sender.setForeground(Color.BLUE);
				sender.setText("X");
                                arre[sender.Field]=-1;
				ComputerMove(1, Color.GREEN,0);
				if ((algo.Gameover(arre)) != 0)
					SetCounters(algo.isGameOver(arre));
			}
		}
	}

	private void NewGame() {
		C1.setText("");
		C2.setText("");
		C3.setText("");
		C4.setText("");
		C5.setText("");
		C6.setText("");
		C7.setText("");
		C8.setText("");
		C9.setText("");
		for(int i=0;i<9;i++){
                    arre[i]=3;
                }
	}
	
	private void CvC() {
		int p = 1;
		int GO = 0;
		NewGame();
		Random rnd = new Random();
		int FirstMove =rnd.nextInt(9) + 1;
		ComputerMove(1, Color.RED,FirstMove-1);
		while (GO == 0) {
			if ((p % 2) == 0) {
				ComputerMove(1, Color.RED,0);
			} else {
				ComputerMove(-1, Color.GREEN,0);
				
			}
			GO = algo.Gameover(arre);
			p++;
		}
		SetCounters(GO);

	}

	private void ComputerMove(int player, Color pcolor,int move) {
		if (move==0) 
			move = algo.Gameover(arre) == 0 ? algo.movimiento(player,arre) : 10;
		String PText = (player == -1) ? "X" : "O";

		switch (move) {
		case 0:
                        arre[move]=player;
			C1.setForeground(pcolor);
			C1.setText(PText);
			
			break;
		case 1:
                        arre[move]=player;
			C2.setForeground(pcolor);
			C2.setText(PText);
			
			break;
		case 2:
                        arre[move]=player;
			C3.setForeground(pcolor);
			C3.setText(PText);
			
			break;
		case 3:
                        arre[move]=player;
			C4.setForeground(pcolor);
			C4.setText(PText);
			
			break;
		case 4:
                        arre[move]=player;
			C5.setForeground(pcolor);
			C5.setText(PText);
			
			break;
		case 5:
                        arre[move]=player;
			C6.setForeground(pcolor);
			C6.setText(PText);
			
			break;
		case 6:
                        arre[move]=player;
			C7.setForeground(pcolor);
			C7.setText(PText);
			
			break;
		case 7:
                        arre[move]=player;
			C8.setForeground(pcolor);
			C8.setText(PText);
			
			break;
		case 8:
                        arre[move]=player;
			C9.setForeground(pcolor);
			C9.setText(PText);
			
			break;
		}

	}
}