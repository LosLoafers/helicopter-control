

xchannel=Channel(32)
uchannel=Channel(32)

global x_remote=0
put!(xchannel,x_remote)

global u_remote=0
put!(uchannel,u_remote)
  Su=ReentrantLock()
  Sx=ReentrantLock()

kalman=@spawn begin
  x=0
global u_remote=0
global x_remote=0
  while true
    x=x+1

    lock(Su)

      u=u_remote

    unlock(Su)

    lock(Sx)

    x_remote=x;
    unlock(Sx)

    println("on kalman ",u)
    sleep(0.1)
  end

end


MPC=@spawn begin
  u=0
  global u_remote=0
  global x_remote=0
  while true
    u=u+1
    lock(Sx)

      x_hat=x_remote;

    unlock(Sx)
    lock(Su)
    u_remote=u
    unlock(Su)

    println("on MPC ",x_hat)

    sleep(0.2)
  end
end
